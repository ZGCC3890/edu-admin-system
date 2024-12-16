# edu-admin-system
Introduction to Software Engineering Course Design

### 连接配置
本项目所有数据库连接使用华为云openGauss数据库，并使用Postgresql官方提供的cpp接口库libpqxx连接<br>
连接配置在config.txt中<br> 
localConnection：模拟本地数据库连接配置字符串<br>
cloudConnection：模拟云端数据库连接配置字符串

### 文件说明
graphFunctions 图形库封装函数及其头文件<br>
studentManagement 学生管理<br>
teacherManagement 教师管理<br>
announceManagement 公告管理<br>
userManagement 用户管理<br>
ustil.h 汇总头文件<br>
具体函数功能见头文件内注释
