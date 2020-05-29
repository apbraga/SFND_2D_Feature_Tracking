# SFND 2D Feature Tracking

<img src="images/keypoints.png" width="820" height="248" />

The idea of the camera course is to build a collision detection system - that's the overall goal for the Final Project. As a preparation for this, you will now build the feature tracking part and test various detector / descriptor combinations to see which ones perform best. This mid-term project consists of four parts:

* First, you will focus on loading images, setting up data structures and putting everything into a ring buffer to optimize memory load. 
* Then, you will integrate several keypoint detectors such as HARRIS, FAST, BRISK and SIFT and compare them with regard to number of keypoints and speed. 
* In the next part, you will then focus on descriptor extraction and matching using brute force and also the FLANN approach we discussed in the previous lesson. 
* In the last part, once the code framework is complete, you will test the various algorithms in different combinations and compare them with regard to some performance measures. 

See the classroom instruction and code comments for more details on each of these parts. Once you are finished with this project, the keypoint matching part will be set up and you can proceed to the next lesson, where the focus is on integrating Lidar points and on object detection using deep-learning. 

## Performance considerations
By running all combination of keypoint detectors, descriptors, matchers and selectors with a total of 126 valid combinations, we got the following result per combination in matches / milisecond order, with the first 3 representing the top 3 performers for this application:

|  DETECTOR | DESCRIPTOR |  MATCHER  | SELECTOR | TOTAL_KEYPOINTS | TOTAL_MATCHES | TOTAL_TIME | MATCHES/TIME |
|:---------:|:----------:|:---------:|:--------:|:---------------:|:-------------:|:----------:|:------------:|
|    FAST   |     ORB    |   MAT_BF  |  SEL_NN  |       1491      |      1348     |      8     |  TOP 1 :152     |
|    FAST   |    FREAK   |   MAT_BF  |  SEL_NN  |       1491      |      1348     |      8     |  TOP 2 : 151     |
|    FAST   |    BRIEF   |   MAT_BF  |  SEL_NN  |       1491      |      1348     |      9     |  TOP3 : 145     |
|    FAST   |    BRISK   |   MAT_BF  |  SEL_NN  |       1491      |      1348     |      9     |      137     |
|    FAST   |    BRIEF   |   MAT_BF  |  SEL_KNN |       1491      |      1099     |      8     |      127     |
|    FAST   |     ORB    |   MAT_BF  |  SEL_KNN |       1491      |      1081     |      8     |      124     |
|    FAST   |    FREAK   |   MAT_BF  |  SEL_KNN |       1491      |      881      |      8     |      99      |
|    FAST   |    BRISK   |   MAT_BF  |  SEL_KNN |       1491      |      899      |      9     |      96      |
|    FAST   |     ORB    | MAT_FLANN |  SEL_NN  |       1491      |      1348     |     19     |      67      |
|    FAST   |    BRIEF   | MAT_FLANN |  SEL_NN  |       1491      |      1348     |     21     |      63      |
|    FAST   |    BRISK   | MAT_FLANN |  SEL_NN  |       1491      |      1348     |     23     |      57      |
|    FAST   |    FREAK   | MAT_FLANN |  SEL_NN  |       1491      |      1348     |     23     |      57      |
|    FAST   |    SIFT    | MAT_FLANN |  SEL_NN  |       1491      |      1348     |     27     |      48      |
|    FAST   |    BRIEF   | MAT_FLANN |  SEL_KNN |       1491      |      889      |     21     |      41      |
|    FAST   |     ORB    | MAT_FLANN |  SEL_KNN |       1491      |      868      |     21     |      40      |
|    FAST   |    SIFT    | MAT_FLANN |  SEL_KNN |       1491      |      1049     |     30     |      34      |
|    FAST   |    BRISK   | MAT_FLANN |  SEL_KNN |       1491      |      782      |     24     |      31      |
|    FAST   |    FREAK   | MAT_FLANN |  SEL_KNN |       1491      |      668      |     26     |      25      |
|    ORB    |    BRIEF   |   MAT_BF  |  SEL_NN  |       1161      |      1033     |     60     |      17      |
|    ORB    |     ORB    |   MAT_BF  |  SEL_NN  |       1161      |      1033     |     58     |      17      |
|    ORB    |    BRIEF   | MAT_FLANN |  SEL_NN  |       1161      |      1033     |     68     |      15      |
|    ORB    |     ORB    | MAT_FLANN |  SEL_NN  |       1161      |      1033     |     73     |      14      |
| SHITOMASI |    BRISK   |   MAT_BF  |  SEL_NN  |       1179      |      1067     |     81     |      13      |
| SHITOMASI |    BRIEF   |   MAT_BF  |  SEL_NN  |       1179      |      1067     |     77     |      13      |
| SHITOMASI |    FREAK   |   MAT_BF  |  SEL_NN  |       1179      |      1067     |     76     |      13      |
|    ORB    |    BRISK   | MAT_FLANN |  SEL_NN  |       1161      |      950      |     70     |      13      |
|    ORB    |     ORB    |   MAT_BF  |  SEL_KNN |       1161      |      761      |     55     |      13      |
| SHITOMASI |    BRISK   | MAT_FLANN |  SEL_NN  |       1179      |      1067     |     84     |      12      |
| SHITOMASI |     ORB    |   MAT_BF  |  SEL_NN  |       1179      |      1067     |     82     |      12      |
| SHITOMASI |     ORB    |   MAT_BF  |  SEL_KNN |       1179      |      907      |     75     |      12      |
| SHITOMASI |     ORB    | MAT_FLANN |  SEL_NN  |       1179      |      1067     |     86     |      12      |
|    ORB    |    BRISK   |   MAT_BF  |  SEL_KNN |       1161      |      751      |     59     |      12      |
| SHITOMASI |    BRIEF   |   MAT_BF  |  SEL_KNN |       1179      |      944      |     79     |      11      |
| SHITOMASI |    BRIEF   | MAT_FLANN |  SEL_NN  |       1179      |      1067     |     90     |      11      |
| SHITOMASI |    FREAK   | MAT_FLANN |  SEL_NN  |       1179      |      1067     |     92     |      11      |
| SHITOMASI |    BRISK   |   MAT_BF  |  SEL_KNN |       1179      |      767      |     73     |      10      |
| SHITOMASI |    BRIEF   | MAT_FLANN |  SEL_KNN |       1179      |      816      |     80     |      10      |
| SHITOMASI |    FREAK   |   MAT_BF  |  SEL_KNN |       1179      |      766      |     73     |      10      |
| SHITOMASI |     ORB    | MAT_FLANN |  SEL_KNN |       1179      |      767      |     84     |       9      |
| SHITOMASI |    SIFT    | MAT_FLANN |  SEL_NN  |       1179      |      1067     |     116    |       9      |
|    ORB    |    BRISK   |   MAT_BF  |  SEL_NN  |       1161      |      950      |     96     |       9      |
|    ORB    |    BRIEF   |   MAT_BF  |  SEL_KNN |       1161      |      545      |     55     |       9      |
|    ORB    |    FREAK   |   MAT_BF  |  SEL_NN  |       1161      |      549      |     57     |       9      |
| SHITOMASI |    SIFT    | MAT_FLANN |  SEL_KNN |       1179      |      927      |     111    |       8      |
|    ORB    |    FREAK   | MAT_FLANN |  SEL_NN  |       1161      |      549      |     63     |       8      |
| SHITOMASI |    BRISK   | MAT_FLANN |  SEL_KNN |       1179      |      687      |     88     |       7      |
|    ORB    |     ORB    | MAT_FLANN |  SEL_KNN |       1161      |      524      |     66     |       7      |
|    ORB    |    FREAK   |   MAT_BF  |  SEL_KNN |       1161      |      421      |     57     |       7      |
|    ORB    |    SIFT    | MAT_FLANN |  SEL_NN  |       1161      |      1033     |     138    |       7      |
|    ORB    |    SIFT    | MAT_FLANN |  SEL_KNN |       1161      |      765      |     106    |       7      |
| SHITOMASI |    FREAK   | MAT_FLANN |  SEL_KNN |       1179      |      577      |     87     |       6      |
|    ORB    |    BRISK   | MAT_FLANN |  SEL_KNN |       1161      |      652      |     97     |       6      |
|    ORB    |    BRIEF   | MAT_FLANN |  SEL_KNN |       1161      |      454      |     66     |       6      |
|    ORB    |    FREAK   | MAT_FLANN |  SEL_KNN |       1161      |      350      |     63     |       5      |
|   HARRIS  |    FREAK   |   MAT_BF  |  SEL_NN  |       359       |      327      |     80     |       4      |
|   HARRIS  |    BRISK   |   MAT_BF  |  SEL_NN  |       359       |      327      |     92     |       3      |
|   HARRIS  |    BRISK   | MAT_FLANN |  SEL_NN  |       359       |      327      |     102    |       3      |
|   HARRIS  |    BRIEF   |   MAT_BF  |  SEL_NN  |       359       |      327      |     81     |       3      |
|   HARRIS  |    BRIEF   | MAT_FLANN |  SEL_NN  |       359       |      327      |     91     |       3      |
|   HARRIS  |     ORB    |   MAT_BF  |  SEL_NN  |       359       |      327      |     99     |       3      |
|   HARRIS  |     ORB    | MAT_FLANN |  SEL_NN  |       359       |      327      |     101    |       3      |
|   HARRIS  |    BRISK   |   MAT_BF  |  SEL_KNN |       359       |      195      |     92     |       2      |
|   HARRIS  |    BRIEF   |   MAT_BF  |  SEL_KNN |       359       |      194      |     75     |       2      |
|   HARRIS  |     ORB    |   MAT_BF  |  SEL_KNN |       359       |      209      |     88     |       2      |
|   HARRIS  |     ORB    | MAT_FLANN |  SEL_KNN |       359       |      182      |     78     |       2      |
|   HARRIS  |    FREAK   |   MAT_BF  |  SEL_KNN |       359       |      208      |     99     |       2      |
|   HARRIS  |    FREAK   | MAT_FLANN |  SEL_NN  |       359       |      327      |     122    |       2      |
|   HARRIS  |    SIFT    | MAT_FLANN |  SEL_NN  |       359       |      327      |     121    |       2      |
|   AKAZE   |    BRISK   | MAT_FLANN |  SEL_NN  |       1670      |      1491     |     674    |       2      |
|   HARRIS  |    BRISK   | MAT_FLANN |  SEL_KNN |       359       |      156      |     100    |       1      |
|   HARRIS  |    BRIEF   | MAT_FLANN |  SEL_KNN |       359       |      163      |     123    |       1      |
|   HARRIS  |    FREAK   | MAT_FLANN |  SEL_KNN |       359       |      134      |     84     |       1      |
|   HARRIS  |    SIFT    | MAT_FLANN |  SEL_KNN |       359       |      191      |     160    |       1      |
|   BRISK   |    BRISK   |   MAT_BF  |  SEL_NN  |       2762      |      2508     |    1745    |       1      |
|   BRISK   |    BRISK   | MAT_FLANN |  SEL_NN  |       2762      |      2508     |    1738    |       1      |
|   BRISK   |    BRIEF   |   MAT_BF  |  SEL_NN  |       2762      |      2508     |    1703    |       1      |
|   BRISK   |    BRIEF   |   MAT_BF  |  SEL_KNN |       2762      |      1704     |    1691    |       1      |
|   BRISK   |    BRIEF   | MAT_FLANN |  SEL_NN  |       2762      |      2508     |    1736    |       1      |
|   BRISK   |     ORB    |   MAT_BF  |  SEL_NN  |       2762      |      2508     |    1697    |       1      |
|   BRISK   |     ORB    | MAT_FLANN |  SEL_NN  |       2762      |      2508     |    1675    |       1      |
|   BRISK   |    FREAK   |   MAT_BF  |  SEL_NN  |       2762      |      2326     |    1696    |       1      |
|   BRISK   |    FREAK   | MAT_FLANN |  SEL_NN  |       2762      |      2326     |    1761    |       1      |
|   BRISK   |    SIFT    | MAT_FLANN |  SEL_NN  |       2762      |      2508     |    2086    |       1      |
|   AKAZE   |    BRISK   |   MAT_BF  |  SEL_NN  |       1670      |      1491     |     876    |       1      |
|   AKAZE   |    BRISK   |   MAT_BF  |  SEL_KNN |       1670      |      1215     |     743    |       1      |
|   AKAZE   |    BRISK   | MAT_FLANN |  SEL_KNN |       1670      |      1119     |    1027    |       1      |
|   AKAZE   |    BRIEF   |   MAT_BF  |  SEL_NN  |       1670      |      1491     |    1032    |       1      |
|   AKAZE   |    BRIEF   |   MAT_BF  |  SEL_KNN |       1670      |      1266     |    1046    |       1      |
|   AKAZE   |    BRIEF   | MAT_FLANN |  SEL_NN  |       1670      |      1491     |    1195    |       1      |
|   AKAZE   |    BRIEF   | MAT_FLANN |  SEL_KNN |       1670      |      1093     |    1078    |       1      |
|   AKAZE   |     ORB    |   MAT_BF  |  SEL_NN  |       1670      |      1491     |     990    |       1      |
|   AKAZE   |     ORB    |   MAT_BF  |  SEL_KNN |       1670      |      1186     |    1001    |       1      |
|   AKAZE   |     ORB    | MAT_FLANN |  SEL_NN  |       1670      |      1491     |    1082    |       1      |
|   AKAZE   |    FREAK   |   MAT_BF  |  SEL_NN  |       1670      |      1491     |    1076    |       1      |
|   AKAZE   |    FREAK   |   MAT_BF  |  SEL_KNN |       1670      |      1188     |     981    |       1      |
|   AKAZE   |    FREAK   | MAT_FLANN |  SEL_NN  |       1670      |      1491     |    1086    |       1      |
|   AKAZE   |    AKAZE   |   MAT_BF  |  SEL_NN  |       1670      |      1491     |    1036    |       1      |
|   AKAZE   |    AKAZE   |   MAT_BF  |  SEL_KNN |       1670      |      1259     |    1080    |       1      |
|   AKAZE   |    AKAZE   | MAT_FLANN |  SEL_NN  |       1670      |      1491     |    1072    |       1      |
|   AKAZE   |    AKAZE   | MAT_FLANN |  SEL_KNN |       1670      |      1171     |    1104    |       1      |
|   AKAZE   |    SIFT    | MAT_FLANN |  SEL_NN  |       1670      |      1491     |    1135    |       1      |
|   AKAZE   |    SIFT    | MAT_FLANN |  SEL_KNN |       1670      |      1280     |    1072    |       1      |
|    SIFT   |    BRISK   |   MAT_BF  |  SEL_NN  |       1386      |      1248     |    1190    |       1      |
|    SIFT   |    BRISK   | MAT_FLANN |  SEL_NN  |       1386      |      1248     |    1159    |       1      |
|    SIFT   |    BRIEF   |   MAT_BF  |  SEL_NN  |       1386      |      1249     |    1001    |       1      |
|    SIFT   |    BRIEF   | MAT_FLANN |  SEL_NN  |       1386      |      1249     |     885    |       1      |
|    SIFT   |    FREAK   |   MAT_BF  |  SEL_NN  |       1386      |      1239     |    1223    |       1      |
|    SIFT   |    FREAK   | MAT_FLANN |  SEL_NN  |       1386      |      1239     |     888    |       1      |
|    SIFT   |    SIFT    | MAT_FLANN |  SEL_NN  |       1386      |      1249     |     819    |       1      |
|    SIFT   |    SIFT    | MAT_FLANN |  SEL_KNN |       1386      |      802      |     755    |       1      |
|   BRISK   |    BRISK   |   MAT_BF  |  SEL_KNN |       2762      |      1570     |    1703    |      <1      |
|   BRISK   |    BRISK   | MAT_FLANN |  SEL_KNN |       2762      |      1313     |    1750    |      <1      |
|   BRISK   |    BRIEF   | MAT_FLANN |  SEL_KNN |       2762      |      1371     |    1774    |      <1      |
|   BRISK   |     ORB    |   MAT_BF  |  SEL_KNN |       2762      |      1510     |    1719    |      <1      |
|   BRISK   |     ORB    | MAT_FLANN |  SEL_KNN |       2762      |      949      |    1713    |      <1      |
|   BRISK   |    FREAK   |   MAT_BF  |  SEL_KNN |       2762      |      1526     |    1683    |      <1      |
|   BRISK   |    FREAK   | MAT_FLANN |  SEL_KNN |       2762      |      1107     |    1691    |      <1      |
|   BRISK   |    SIFT    | MAT_FLANN |  SEL_KNN |       2762      |      1662     |    2308    |      <1      |
|   AKAZE   |     ORB    | MAT_FLANN |  SEL_KNN |       1670      |      930      |    1039    |      <1      |
|   AKAZE   |    FREAK   | MAT_FLANN |  SEL_KNN |       1670      |      967      |    1051    |      <1      |
|    SIFT   |    BRISK   |   MAT_BF  |  SEL_KNN |       1386      |      592      |    1124    |      <1      |
|    SIFT   |    BRISK   | MAT_FLANN |  SEL_KNN |       1386      |      540      |    1164    |      <1      |
|    SIFT   |    BRIEF   |   MAT_BF  |  SEL_KNN |       1386      |      702      |     862    |      <1      |
|    SIFT   |    BRIEF   | MAT_FLANN |  SEL_KNN |       1386      |      600      |     835    |      <1      |
|    SIFT   |    FREAK   |   MAT_BF  |  SEL_KNN |       1386      |      596      |     928    |      <1      |
|    SIFT   |    FREAK   | MAT_FLANN |  SEL_KNN |       1386      |      503      |    1025    |      <1      |

The following combinations are invalid:

|  DETECTOR | DESCRIPTOR |  MATCHER  | SELECTOR |
|:---------:|:----------:|:---------:|:--------:|
| SHITOMASI | AKAZE      | MAT_BF    | SEL_NN   |
| SHITOMASI | AKAZE      | MAT_BF    | SEL_KNN  |
| SHITOMASI | AKAZE      | MAT_FLANN | SEL_NN   |
| SHITOMASI | AKAZE      | MAT_FLANN | SEL_KNN  |
| SHITOMASI | SIFT       | MAT_BF    | SEL_NN   |
| SHITOMASI | SIFT       | MAT_BF    | SEL_KNN  |
| HARRIS    | AKAZE      | MAT_BF    | SEL_NN   |
| HARRIS    | AKAZE      | MAT_BF    | SEL_KNN  |
| HARRIS    | AKAZE      | MAT_FLANN | SEL_NN   |
| HARRIS    | AKAZE      | MAT_FLANN | SEL_KNN  |
| HARRIS    | SIFT       | MAT_BF    | SEL_NN   |
| HARRIS    | SIFT       | MAT_BF    | SEL_KNN  |
| FAST      | AKAZE      | MAT_BF    | SEL_NN   |
| FAST      | AKAZE      | MAT_BF    | SEL_KNN  |
| FAST      | AKAZE      | MAT_FLANN | SEL_NN   |
| FAST      | AKAZE      | MAT_FLANN | SEL_KNN  |
| FAST      | SIFT       | MAT_BF    | SEL_NN   |
| FAST      | SIFT       | MAT_BF    | SEL_KNN  |
| BRISK     | AKAZE      | MAT_BF    | SEL_NN   |
| BRISK     | AKAZE      | MAT_BF    | SEL_KNN  |
| BRISK     | AKAZE      | MAT_FLANN | SEL_NN   |
| BRISK     | AKAZE      | MAT_FLANN | SEL_KNN  |
| BRISK     | SIFT       | MAT_BF    | SEL_NN   |
| BRISK     | SIFT       | MAT_BF    | SEL_KNN  |
| ORB       | AKAZE      | MAT_BF    | SEL_NN   |
| ORB       | AKAZE      | MAT_BF    | SEL_KNN  |
| ORB       | AKAZE      | MAT_FLANN | SEL_NN   |
| ORB       | AKAZE      | MAT_FLANN | SEL_KNN  |
| ORB       | SIFT       | MAT_BF    | SEL_NN   |
| ORB       | SIFT       | MAT_BF    | SEL_KNN  |
| AKAZE     | SIFT       | MAT_BF    | SEL_NN   |
| AKAZE     | SIFT       | MAT_BF    | SEL_KNN  |
| SIFT      | ORB        | MAT_BF    | SEL_NN   |
| SIFT      | ORB        | MAT_BF    | SEL_KNN  |
| SIFT      | ORB        | MAT_FLANN | SEL_NN   |
| SIFT      | ORB        | MAT_FLANN | SEL_KNN  |
| SIFT      | AKAZE      | MAT_BF    | SEL_NN   |
| SIFT      | AKAZE      | MAT_BF    | SEL_KNN  |
| SIFT      | AKAZE      | MAT_FLANN | SEL_NN   |
| SIFT      | AKAZE      | MAT_FLANN | SEL_KNN  |
| SIFT      | SIFT       | MAT_BF    | SEL_NN   |
| SIFT      | SIFT       | MAT_BF    | SEL_KNN  |



## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * This must be compiled from source using the `-D OPENCV_ENABLE_NONFREE=ON` cmake flag for testing the SIFT and SURF detectors.
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./2D_feature_tracking`.
