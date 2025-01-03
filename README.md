# edu-admin-system
一个小型教务系统demo
## 目录
<ul>
  <li><a href = "#section1">连接配置</a></li>
  <li><a href = "#section2">源文件说明</a></li>
  <li><a href = "#section3">运行环境</a></li>
  <li><a href = "#section4">命名格式</a></li>
  <li><a href = "#section5">项目说明</a></li>
  <li><a href = "#section6">数据库说明</a></li>
</ul>

### <h3 id = "section1">连接配置</h3>
本项目所有数据库连接使用华为云openGauss数据库，并使用Postgresql官方提供的cpp接口库libpqxx连接<br>
连接配置在config.txt中  
localConnection：模拟本地数据库连接配置字符串  
cloudConnection：模拟云端数据库连接配置字符串  
#### 配置样例
```
localConnection = dbname=<数据库名> user=<用户名> password=<密码> host=<主机地址> port=<端口> options='-c client_encoding=UTF8'
```
libpqxx仅支持使用md5加密密码，请在服务器配置中修改本地监听127.0.0.1加密方式为md5并修改密码以重新以md5方式存储

### <h3 id = "section2">源文件说明</h3>
graphFunctions 图形库封装函数及其头文件  
studentManagement 学生管理  
teacherManagement 教师管理  
announceManagement 公告管理  
userManagement 用户管理  
ustil.h 汇总头文件  
具体函数功能见头文件内注释

### <h3 id = "section3">运行环境</h3>
#### 系统
**Windows 10以上**  
&nbsp;&nbsp;&nbsp;&nbsp;在win11上编写，但win10运行应该也可运行
#### 图形库
**easyx**  
&nbsp;&nbsp;&nbsp;&nbsp;./easyx目录下自带
#### 数据库及连接接口
**libpqxx**  
&nbsp;&nbsp;&nbsp;&nbsp;在./libpqxx目录下自带  
本地需要安装**PostgreSQL**（需要其提供的libpq）用于远程连接  
&nbsp;&nbsp;&nbsp;&nbsp;官方下载地址：https://www.postgresql.org/download/  
&nbsp;&nbsp;&nbsp;&nbsp;安装后如果不是默认路径安装，请自行更改./cmakelist.txt中的  
```
set(PostgreSQL_INCLUDE_DIR "C:/Program Files/PostgreSQL/17/include")
set(PostgreSQL_LIBRARY "C:/Program Files/PostgreSQL/17/lib/libpq.lib")
```
&nbsp;&nbsp;&nbsp;&nbsp;这两行目录为安装目录  
&nbsp;&nbsp;&nbsp;&nbsp;最后如果报错找不到.dll请将lib和bin目录加入系统环境变量   
&nbsp;&nbsp;&nbsp;&nbsp;*C:\Program Files\PostgreSQL\17\lib*  
&nbsp;&nbsp;&nbsp;&nbsp;*C:\Program Files\PostgreSQL\17\bin*
#### 其他工具
需要**pkg-config**，windows不自带，需要自行安装，可参考
https://blog.csdn.net/LuckyHanMo/article/details/125471360
<br>安装后在终端输入`pkg-config`检查是否安装成功

### <h3 id = "section4">命名格式</h3>
1. 函数——首字母均大写  
ExampleFunction()
2. bool型标志——首字母小写后续单词首字母大写，最后以下划线结尾  
exampleBool_
3. 存储用string——变量名前加"s_"   
string s_exampleString

### <h3 id = "section5">项目说明</h3>
branch-main：主支，一个模块完整实现+注释完全后推送  
branch-release：阶段性进度存储  
branch-feature：开发分支，随时推送  

### <h3 id = "section6">数据库说明</h3>
<table>
  <tr>
    <th>表名</th>
    <th>列名</th>
    <th>数据类型</th>
    <th>用途</th>
    <th>备注</th>
  </tr>
  <tr>
    <td rowspan="4">users</td>
    <td>user_id</td>
    <td>VARCHAR(50)</td>
    <td>用户id</td>
    <td></td>
  </tr>
  <tr>
    <td>name</td>
    <td>VARCHAR(100)</td>
    <td>用户姓名</td>
    <td></td>
  </tr>
  <tr>
    <td>identity</td>
    <td>VARCHAR(20)</td>
    <td>用户身份</td>
    <td><a href="#dataNoteIdentity">见数据内容说明.identity</a></td>
  </tr>
  <tr>
    <td>password</td>
    <td>VARCHAR(255)</td>
    <td>用户密码</td>
    <td></td>
  </tr>
  <tr>
    <td rowspan="5">students</td>
    <td>student_id</td>
    <td>VARCHAR(50)</td>
    <td>学生学号</td>
    <td></td>
  </tr>
  <tr>
    <td>name</td>
    <td>VARCHAR(100)</td>
    <td>学生姓名</td>
    <td></td>
  </tr>
  <tr>
    <td>major</td>
    <td>VARCHAR(100)</td>
    <td>学生专业</td>
    <td><a href="#dataNoteMajor">见数据内容说明.major</a></td>
  </tr>
  <tr>
    <td>grade</td>
    <td>INTEGER</td>
    <td>学生年级</td>
    <td>exp. 2024</td>
  </tr>
  <tr>
    <td>class</td>
    <td>INTEGER</td>
    <td>学生班级</td>
    <td>exp. 1</td>
  </tr>
  <tr>
    <td rowspan="5">teachers</td>
    <td>teacher_id</td>
    <td>VARCHAR(50)</td>
    <td>教师教工号</td>
    <td></td>
  </tr>
  <tr>
    <td>name</td>
    <td>VARCHAR(100)</td>
    <td>教师姓名</td>
    <td>不带职称前缀</td>
  </tr>
  <tr>
    <td>faculty</td>
    <td>VARCHAR(100)</td>
    <td>教师院系</td>
    <td><a href = "#dataNoteFaculty">见数据内容说明.faculty</a></td>
  </tr>
  <tr>
    <td>title</td>
    <td>VARCHAR(50)</td>
    <td>教师职称</td>
    <td><a href="#dataNoteTitle">见数据内容说明.title</a></td>
  </tr>
  <tr>
    <td>email</td>
    <td>VARCHAR(50)</td>
    <td>电子邮件</td>
    <td></td>
  </tr>
  <tr>
    <td rowspan="3">admins</td>
    <td>admin_id</td>
    <td>VARCHAR(50)</td>
    <td>管理员工号</td>
    <td></td>
  </tr>
  <tr>
    <td>name</td>
    <td>VARCHAR(100)</td>
    <td>管理员姓名</td>
    <td></td>
  </tr>
  <tr>
    <td>privilege</td>
    <td>INTEGER</td>
    <td>权限等级</td>
    <td><a href="#dataNotePrivilege">见数据内容说明.privilege</a></td>
  </tr>
  <tr>
    <td rowspan="4">enrollments</td>
    <td>student_id</td>
    <td>VARCHAR(50)</td>
    <td>学生学号</td>
    <td></td>
  </tr>
  <tr>
    <td>course_id</td>
    <td>VARCHAR(50)</td>
    <td>课程编号</td>
    <td></td>
  </tr>
  <tr>
    <td>operation</td>
    <td>VARCHAR(20)</td>
    <td>操作</td>
    <td><a href="#dataNoteOperation">见数据内容说明.operation</a></td>
  </tr>
  <tr>
    <td>enrollment_date</td>
    <td>TIMESTAMP</td>
    <td>操作时间</td>
    <td></td>
  </tr>
  <tr>
    <td rowspan="8">courses</td>
    <td>courses_id</td>
    <td>VARCHAR(100)</td>
    <td>课程编号</td>
    <td></td>
  </tr>
  <tr>
    <td>course_name</td>
    <td>VARCHAR(100)</td>
    <td>课程名称</td>
    <td></td>
  </tr>
  <tr>
    <td>teacher_name</td>
    <td>VARCHAR(100)</td>
    <td>教师名称</td>
    <td><a href="#dataNoteTitle">带职称前缀，见teachers.title</a></td>
  </tr>
  <tr>
    <td>schedule</td>
    <td>VARCHAR(100)</td>
    <td>上课时间</td>
    <td></td>
  </tr>
  <tr>
    <td>current_students</td>
    <td>INTEGER</td>
    <td>当前选课人数</td>
    <td></td>
  </tr>
  <tr>
    <td>max_students</td>
    <td>INTEGER</td>
    <td>选课人数上限</td>
    <td></td>
  </tr>
  <tr>
    <td>classroom</td>
    <td>VARCHAR(50)</td>
    <td>上课教室</td>
    <td>exp. Room B100</td>
  </tr>
  <tr>
    <td>major_restriction</td>
    <td>VARCHAR(100)</td>
    <td>专业限制</td>
    <td><a href="#dataNoteMajor">同students.major</a></td>
  </tr>
  <tr>
    <td rowspan="5">scores</td>
    <td>student_id</td>
    <td>VARCHAR(50)</td>
    <td>学生学号</td>
    <td></td>
  </tr>
  <tr>
    <td>exam_name</td>
    <td>VARCHAR(100)</td>
    <td>考试名称</td>
    <td></td>
  </tr>
  <tr>
    <td>grade</td>
    <td>NUMERIC(5,2)</td>
    <td>考试分数</td>
    <td></td>
  </tr>
  <tr>
    <td>session</td>
    <td>VARCHAR(20)</td>
    <td>考试学期</td>
    <td>exp. 2024-1</td>
  </tr>
  <tr>
    <td>teacher_id</td>
    <td>VARCHAR(50)</td>
    <td>教师教工号</td>
    <td></td>
  </tr>
  <tr>
    <td rowspan="5">projects</td>
    <td>project_id</td>
    <td>VARCHAR(50)</td>
    <td>项目编号</td>
    <td></td>
  </tr>
  <tr>
    <td>teacher_id</td>
    <td>VARCHAR(50)</td>
    <td>教师教工号</td>
    <td></td>
  </tr>
  <tr>
    <td>name</td>
    <td>VARCHAR(100)</td>
    <td>项目名称</td>
    <td></td>
  </tr>
  <tr>
    <td>budget</td>
    <td>NUMERIC(10, 2)</td>
    <td>项目预算</td>
    <td>exp. 200000.00</td>
  </tr>
  <tr>
    <td>creation_time</td>
    <td>VARCHAR(20)</td>
    <td>立项时间</td>
    <td>exp. 2024.1</td>
  </tr>
  <tr>
    <td rowspan="4">members</td>
    <td>project_id</td>
    <td>VARCHAR(50)</td>
    <td>项目编号</td>
    <td></td>
  </tr>
  <tr>
    <td>teacher_id</td>
    <td>VARCHAR(50)</td>
    <td>教师教工号</td>
    <td></td>
  </tr>
  <tr>
    <td>student_id</td>
    <td>VARCHAR(50)</td>
    <td>学生学号</td>
    <td></td>
  </tr>
  <tr>
    <td>join_time</td>
    <td>TIMESTAMP</td>
    <td>加入时间</td>
    <td></td>
  </tr>
  <tr>
    <td rowspan="4">announcements</td>
    <td>title</td>
    <td>VARCHAR(50)</td>
    <td>公告标题</td>
    <td></td>
  </tr>
  <tr>
    <td>article</td>
    <td>VARCHAR(1000)</td>
    <td>公告内容</td>
    <td></td>
  </tr>
  <tr>
    <td>author_id</td>
    <td>VARCHAR(50)</td>
    <td>作者用户编号</td>
    <td></td>
  </tr>
  <tr>
    <td>publish_time</td>
    <td>TIMESTAMP</td>
    <td>发布时间</td>
    <td></td>
  </tr>
</table>

#### 数据内容说明
<table>
  <tr>
    <th>列名</th>
    <th>可选内容</th>
    <th>备注</th>
  </tr>
  <tr>
    <td rowspan="3" id = "dataNoteIdentity">users.identity</td>
    <td>student</td><td>学生</td>
  </tr>
  <tr><td>teacher</td><td>教师</td></tr>
  <tr><td>admin</td><td>管理员</td></tr>
  <tr>
    <td rowspan="4" id = "dataNoteMajor">students.major</td>
    <td>Computer Science and Technology</td><td>计算机科学与技术</td>
  </tr>
  <tr><td>Physics</td><td>物理</td></tr>
  <tr><td>Mathematics</td><td>数学</td></tr>
  <tr><td>Biology</td><td>生物</td></tr>
  <tr>
    <td rowspan="4" id = "dataNoteFaculty">teachers.faculty</td>
    <td>Computer Science and Technology</td><td>计算机科学与技术</td>
  </tr>
  <tr><td>Physics</td><td>物理</td></tr>
  <tr><td>Biology</td><td>生物</td></tr>
  <tr><td>Mathematics</td><td>数学</td></tr>
  <tr>
    <td rowspan="2" id = "dataNoteOperation">enrollments.operation</td>
    <td>select</td><td>选课</td>
  </tr>
  <tr><td>drop</td><td>退课</td></tr>
  <tr>
    <td rowspan="3" id = "dataNoteTitle">teachers.title</td>
    <td>professor</td><td>Prof.</td>
  </tr>
  <tr><td>doctor</td><td>Dr.</td></tr>
  <tr><td>lecturer</td><td>无前缀</td></tr>
  <tr>
    <td rowspan="4" id = "dataNotePrivilege">admins.privilege</td>
    <td>0</td><td>普通用户</td>
  </tr>
  <tr><td>1</td><td>具有公告系统权限</td></tr>
  <tr><td>2</td><td>具有考试系统操作权限和1级权限</td></tr>
  <tr><td>3</td><td>具有用户管理权限和2级、1级权限</td></tr>
</table>