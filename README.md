# edu-admin-system
Introduction to Software Engineering Course Design

### 连接配置
本项目所有数据库连接使用华为云openGauss数据库，并使用Postgresql官方提供的cpp接口库libpqxx连接<br>

连接配置在config.txt中
<br>localConnection：模拟本地数据库连接配置字符串
<br>cloudConnection：模拟云端数据库连接配置字符串
#### 配置样例
```
localConnection = dbname=<数据库名> user=<用户名> password=<密码> host=<主机地址> port=<端口> options='-c client_encoding=UTF8'
```

### 文件说明
graphFunctions 图形库封装函数及其头文件
<br>studentManagement 学生管理
<br>teacherManagement 教师管理
<br>announceManagement 公告管理
<br>userManagement 用户管理
<br>ustil.h 汇总头文件
<br>具体函数功能见头文件内注释

### 运行环境
#### 图形库
**easyx**
<br>&nbsp;&nbsp;&nbsp;&nbsp;./easyx目录下自带
#### 数据库及连接接口
**libpqxx**
<br>&nbsp;&nbsp;&nbsp;&nbsp;在./libpqxx目录下自带
<br>本地需要安装**PostgreSQL**（需要其提供的libpq）用于远程连接
<br>&nbsp;&nbsp;&nbsp;&nbsp;官方下载地址：https://www.postgresql.org/download/
<br>&nbsp;&nbsp;&nbsp;&nbsp;安装后如果不是默认路径安装，请自行更改./cmakelist.txt中的
```
set(PostgreSQL_INCLUDE_DIR "C:/Program Files/PostgreSQL/17/include")
set(PostgreSQL_LIBRARY "C:/Program Files/PostgreSQL/17/lib/libpq.lib")
```
<br>&nbsp;&nbsp;&nbsp;&nbsp;这两行目录为安装目录
<br>&nbsp;&nbsp;&nbsp;&nbsp;最后如果报错找不到.dll请将lib和bin目录加入系统环境变量
<br>&nbsp;&nbsp;&nbsp;&nbsp;*C:\Program Files\PostgreSQL\17\lib*
<br>&nbsp;&nbsp;&nbsp;&nbsp;*C:\Program Files\PostgreSQL\17\bin*
#### 其他工具
需要**pkg-config**，windows不自带，需要自行安装，可参考
https://blog.csdn.net/LuckyHanMo/article/details/125471360
<br>安装后在终端输入`pkg-config`检查是否安装成功

### 命名格式
1. 函数——首字母均大写  
ExampleFunction()
2. bool型标志——首字母小写后续单词首字母大写，最后以下划线结尾  
exampleBool_
3. 存储用string——变量名前加"s_"   
string s_exampleString

### 项目说明
branch-main：主支，一个模块完整实现+注释完全后推送
branch-release：阶段性进度存储
branch-feature：开发分支，随时推送

