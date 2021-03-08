#include <8051.h>
#define BUZZ  P1 //蜂鸣器控制引脚
unsigned int __code NoteFrequ[] = { //中音 1-7 和高音 1-7 对应频率列表
    523, 587, 659, 698, 784, 880, 988, //中音 1-7
    1047, 1175, 1319, 1397, 1568, 1760, 1976 //高音 1-7
};
unsigned int __code NoteReload[] = { //中音 1-7 和高音 1-7 对应的定时器重载值
    65536 - (11059200/12) / (523*2), //中音 1
    65536 - (11059200/12) / (587*2), //2
    65536 - (11059200/12) / (659*2), //3
    65536 - (11059200/12) / (698*2), //4
    65536 - (11059200/12) / (784*2), //5
    65536 - (11059200/12) / (880*2), //6
    65536 - (11059200/12) / (988*2), //7
    65536 - (11059200/12) / (1047*2), //高音 1
    65536 - (11059200/12) / (1175*2), //2
    65536 - (11059200/12) / (1319*2), //3
    65536 - (11059200/12) / (1397*2), //4
    65536 - (11059200/12) / (1568*2), //5
    65536 - (11059200/12) / (1760*2), //6
    65536 - (11059200/12) / (1976*2), //7
};
__bit enable = 1; //蜂鸣器发声使能标志
__bit tmrflag = 0; //定时器中断完成标志
unsigned char T0RH = 0xFF; //T0 重载值的高字节
unsigned char T0RL = 0x00; //T0 重载值的低字节
void PlayTwoTiger();
void main(){
    unsigned int i;
    EA = 1; //使能全局中断
    TMOD = 0x01; //配置 T0 工作在模式 1
    TH0 = T0RH;
    TL0 = T0RL;
    ET0 = 1; //使能 T0 中断
    TR0 = 1; //启动 T0
   
    while (1){
        PlayTwoTiger(); //播放乐曲--两支老虎
        for (i=0; i<40000; i++); //停止一段时间
    }
}
/* 两支老虎乐曲播放函数 */
void PlayTwoTiger(){
    unsigned char beat; //当前节拍索引
    unsigned char note; //当前节拍对应的音符
    unsigned int time = 0; //当前节拍计时
    unsigned int beatTime = 0; //当前节拍总时间
    unsigned int soundTime = 0; //当前节拍需发声时间
    //两只老虎音符表
    unsigned char __code TwoTigerNote[] = {
    1,   2,   3, 1,    1,   2,   3, 1,     3, 4, 5,   3, 4, 5,
    5,6, 5,4, 3, 1,    5,6, 5,4, 3, 1,     1, 5, 1,   1, 5, 1,
   
    };
    //两只老虎节拍表，4 表示一拍，1 就是 1/4 拍，8 就是 2 拍
    unsigned char __code TwoTigerBeat[] = {
    4,   4,   4, 4,   4,   4,   4, 4,    4, 4, 8,   4, 4, 8,
    3,1, 3,1, 4, 4,   3,1, 3,1, 4, 4,    4, 4, 8,   4, 4, 8,
    };
   
    //用节拍索引作为循环变量
    for (beat=0; beat<sizeof(TwoTigerNote); ){
        while (!tmrflag); //每次定时器中断完成后，检测并处理节拍
        tmrflag = 0;
        if (time == 0){ //当前节拍播完则启动一个新节拍
            note = TwoTigerNote[beat] - 1;
            T0RH = NoteReload[note] >> 8;
            T0RL = NoteReload[note];
            //计算节拍总时间，右移 2 位相当于除 4，移位代替除法可以加快执行速度
            beatTime = (TwoTigerBeat[beat] * NoteFrequ[note]) >> 2;
            //计算发声时间，为总时间的 0.75，移位原理同上
            soundTime = beatTime - (beatTime >> 2);
            enable = 1; //指示蜂鸣器开始发声
            time++;
        }else{ //当前节拍未播完则处理当前节拍
            //当前持续时间到达节拍总时间时归零，
            //并递增节拍索引，以准备启动新节拍
            if (time >= beatTime){
                time = 0;
                beat++;
            }else{ //当前持续时间未达到总时间时，
                time++; //累加时间计数
                //到达发声时间后，指示关闭蜂鸣器，
                //插入 0.25*总时间的静音间隔，
                if (time == soundTime){
                    enable = 0; //用以区分连续的两个节拍
                }
            }
        }
    }
}
/* T0 中断服务函数，用于控制蜂鸣器发声 */
void InterruptTimer0() __interrupt 1{
    TH0 = T0RH; //重新加载重载值
    TL0 = T0RL;
    tmrflag = 1;
    if (enable){ //使能时反转蜂鸣器控制电平
        BUZZ = ~BUZZ;
    }else{ //未使能时关闭蜂鸣器
        BUZZ = 0;
    }
}