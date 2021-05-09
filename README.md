# LL1
 
compile2.cpp(词法分析)
应在D:\\test.txt的位置放入待测代码(代码中读取路径是D盘根目录下)
运行后会在D:\\token.txt中生成token序列
运行compile2.exe

compile3.cpp(输出first和follow集)
应在D:\\first.txt放入文法
然后会在终端输出两个集合，可以自行保存
(压缩包中的first_ans和follow_ans就是生成后的两个集合，也应放在D盘根目录下再进行预测分析)
运行compile3.exe

predict.cpp(预测分析)
分别在D:\\first_ans和D:\\follow_ans存入生成完毕的两种集合
并从D:\\token中读入token序列
预测分析表会生成在D:\\table.txt中(代码中已将这部分注释掉，存起来只是个心理安慰)
最后终端打印LL(1)的产生式序列
运行predict.exe

ps：建议把所有的txt都存到D盘根目录下