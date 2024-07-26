#include "LSM6DSOX.h"
#include <SPI.h>
#include "fft_handler.h"
#include "Kmeans.h"


//Kmeans
int Sample_to_pred[SAMPLES*3];
Kmeans_OT clf;
int kmeans_state=-1;
int sample_1[SAMPLES*3]={1072,2624,136,19176,117168,108088,12376,768,7192,11888,4496,1832,13176,57232,44592,3136,2088,29208,55072,17424,504,43840,46440,32680,2104,2160,29880,43376,10688,3560,9288,34616,19984,720,3504,18352,23712,8792,1472,13792,35528,19280,1400,4368,20224,22136,4072,592,13176,25336,5928,4336,2840,12600,10672,5600,2752,4480,9848,4096,320,2168,9064,8520,2936,336,3944,6376,2936,920,1416,2992,3184,2136,1824,2456,4896,2632,1408,2856,5112,2632,432,488,856,1424,288,608,1264,2984,1600,1776,2432,3792,3688,800,1304,1592,1192,88,1792,984,960,408,192,200,5752,3232,800,1824,2504,376,568,960,688,816,192,112,152,592,2640,1744,152,200,120,232,280,136,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,496,236,1084,6636,39032,34588,4088,3088,10268,20940,7920,2036,3176,13232,10956,2220,2044,18008,28920,23288,2420,2968,13012,10612,2700,3460,12836,16192,5036,2372,1192,1592,476,424,1240,3100,4580,1588,1452,4116,10668,2564,2952,2696,10588,9728,1012,960,11756,24924,11220,1988,3056,9820,7360,2380,2036,4720,8540,1548,800,1368,7156,6288,632,1064,1632,1752,1340,412,1140,3244,2040,468,632,540,920,176,348,704,2076,1448,1028,624,2208,2680,1220,1032,988,1608,1332,300,1104,5660,5780,1776,812,504,388,240,416,764,2980,2480,780,1120,1932,2964,1056,540,884,3092,1392,540,832,256,556,64,520,84,1160,524,532,536,56,188,48,76,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1040,2584,688,3992,18440,17008,1264,2216,42816,82400,29296,1992,8776,42248,33448,3296,1192,28416,47528,14928,2296,8160,27208,18752,2296,1776,4608,6840,3384,2208,8568,21768,13904,2848,2576,11808,13928,2392,3704,3416,10408,6160,6896,6456,4568,2320,4984,6456,11856,22104,6440,4168,8752,16464,13784,1752,2488,7984,13816,3000,2016,2720,9824,7696,1464,2136,3584,3688,1128,1728,1792,7072,5000,808,72,2392,3512,920,560,88,1032,64,1456,1640,1872,2728,976,840,1024,2200,912,360,1296,8104,8056,1072,2360,1032,96,416,1008,1112,3136,2424,496,776,2200,3512,1544,768,672,2272,1664,776,1232,576,352,456,480,392,872,632,672,784,272,120,104,256,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int sample_2[SAMPLES*3]={1064,2096,464,19976,115456,110824,11720,1128,6096,13952,2560,464,10864,57792,46608,5016,1840,30144,50592,17864,992,12968,53944,41424,5152,3288,32128,47664,12048,2520,8144,32264,21768,2504,1832,15736,84600,13144,2960,14064,43360,26352,4112,2136,15344,17120,10448,1736,12208,27296,10120,3456,2856,13896,13552,4632,664,4384,9928,5288,1768,1320,7984,10128,4520,1656,3688,5944,2144,1936,704,2368,2016,2552,1352,1472,2688,1304,1344,2216,6112,4472,1064,744,1160,1032,536,976,1384,3984,1968,2456,2496,4912,4720,672,544,80,1176,288,1528,1048,296,512,1192,696,1528,3136,1048,1408,2200,696,160,976,1080,200,680,240,224,1064,2368,1512,152,144,240,88,56,80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,500,932,740,6700,39440,35828,4316,384,11504,21452,7796,176,2608,14364,11840,2320,152,18372,31384,10772,404,4416,12752,33060,2572,296,5928,10284,1948,420,876,1432,1340,284,1424,5816,19392,2804,672,8020,20320,13616,4712,11668,12504,14672,3880,380,11176,25200,39188,752,1952,9100,9656,3000,1908,4388,8420,4732,2336,2172,24800,7136,1908,612,2384,3604,4332,472,1164,2808,1936,1104,872,1276,1988,956,724,448,1128,920,1316,952,1108,1688,1204,1300,792,1284,900,1272,448,4232,4684,692,1152,708,1548,560,224,420,2292,2072,1028,1008,1524,3072,1096,532,728,1264,568,536,428,204,688,256,440,576,1272,828,384,460,248,172,44,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1040,2584,688,3992,18440,17008,1264,2216,42816,82400,29296,1992,8776,42248,33448,3296,1192,28416,47528,14928,2296,8160,27208,18752,2296,1776,4608,6840,3384,2208,8568,21768,13904,2848,2576,11808,13928,2392,3704,3416,10408,6160,6896,6456,4568,2320,4984,6456,11856,22104,6440,4168,8752,16464,13784,1752,2488,7984,13816,3000,2016,2720,9824,7696,1464,2136,3584,3688,1128,1728,1792,7072,5000,808,72,2392,3512,920,560,88,1032,64,1456,1640,1872,2728,976,840,1024,2200,912,360,1296,8104,8056,1072,2360,1032,96,416,1008,1112,3136,2424,496,776,2200,3512,1544,768,672,2272,1664,776,1232,576,352,456,480,392,872,632,672,784,272,120,104,256,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float start=0;
float end=0;
int counter=0;



void setup() {
  // Initalize serial connection
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  start=micros();
  if(counter<25){
    kmeans_state=clf.predict(sample_1);
    counter++;
  }
  else kmeans_state=clf.predict(sample_2);
  end=micros();
  if(kmeans_state==-1){
    Serial.print("Time for either anomaly or first train samples:");Serial.println(end-start);
  }
  else if(kmeans_state==-2){
    Serial.print("Time for train:");Serial.println(end-start);
  }
  else{
    Serial.print("Time for normal prediction:");Serial.println(end-start);
  }
  delay(500);
  //relevant prints
}