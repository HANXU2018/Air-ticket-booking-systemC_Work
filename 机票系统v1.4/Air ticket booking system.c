#include<stdio.h>
#include<string.h>
#define IDLEN 13//身份证号码长度
#define FLIGHTMAX 100//航班用户最多人数
#define NAMELEN 10//姓名长度
#define PHONELEN 11//电话长度
#define USERFLIGHTMAX 10//用户最多预定航拍数量
#define PASSWORDLEN 10//密码长度


//数据类型存储
typedef struct user_information{//用户信息

	char user_id[15];//账号
	char user_name[NAMELEN];//姓名
	char user_sex[10];//性别
	char user_phonenumber[20];//联系电话
	char user_chinaid[20];//身份证
	char user_bookinginformation[100];//预定的航班信息
	char user_password[20];//密码
	struct user_information* next;
}USER_I;

typedef struct flight_information{
   char flightNo[15];   //航班号
   char start[10];      //起始站
   char end[10];       //终点站
   char day[20];          //飞行时间
   char  totalTicket[10];     //预售票总数
   char  sellTicket[10];      //已售票总数
   char user[FLIGHTMAX][20];//购票用户账号
   
   struct light_information* next;
}FLIGHT_I;  //航班结构体

typedef struct Administrator_information{
	char admin_id[20];//管理员账号
	char admin_password[20];//密码
	struct Administrator_information* next;
}ADMIN_I;

typedef struct PASSWORD{
	char uid[20];//账号 
	char upassword[20];//密码 
	struct PASSWORD* next;
	
}PASSWORD; 

/*基础功能函数
删改使用链表接收所有数据
删改之后从新写入文件 
*/
/**
	读取文件函数 

*/
int readall(void);//初始化读取使用文件 
int readalluser(void);//读取并返回所有用户信息 
int readallflight(void);//读取并返回所有用户信息
int readalladmin(void);//读取并返回所有管理员信息 
int readpassword(void); //读取并返回所有账号密码 


int select_admin();//管理员选择面板 

int showmain();//用户面板展示函数
int showadmin();//管理员面板展示函数




char* login();//登录
int judje(char *x);//判断用户类型
int show(int x);//面板展示函数
/*
	查询 
*/
int searchme(char *x);//客户查询自身信息
int searchflight(char *x);//查询航班信息
int showuser();//所有用户资料
int showflight();//所有飞机资料 

/*
	添加 
*/ 
int adduser();//增加用户 
int addadmin();//增加管理员
int addflight();//增加航班 
/*
	修改 
*/
//修改用户资料
int change_user(char* x);
int change_user_name(char* x);
int change_user_sex(char* x);
int change_user_phone(char* x);
int change_user_chinaid(char* x);
int change_user_password(char* x);
int change_user_flight(char* x); 
//修改航班信息
int change_flight(char* x); 
int change_flight_start(char* x); 
int change_flight_end(char* x); 
int change_flight_day(char* x); 
int change_flight_total(char* x); 
int change_flight_sell(char* x); 
int change_flight_user(char* x); 
//修改管理员密码
int change_admin(char* x);
int change_admin_password(char* x); 
/*

删除功能
1.删除用户
2.删除管理员
3.删除航班 
*/ 
int deleteuser(char *x);
int deleteadmin(char *x);
int deleteflight(char *x); 
int deletepassword(char *x);
int deleteadmin(char* x); 

/**
 保存文件
 1.保存删除用户后用户列表
 2.保存删除航班后航班列表 
*/
int saveall();
int saveuser();
int saveflight(); 
int savesudolist();
int savepassword();

/****
主函数
1.登录
2.显示对应角色面板
3.进行角色操作 

**/


/*
	释放内存 
*/
void freeall();//释放所有内存 
void freeuser_i(USER_I*x);
void freeflight_i(FLIGHT_I* x);
void freepassword(PASSWORD* x);
void freeadmin_i(ADMIN_I* x);


//全局变量 
int type; 
char *UID;
USER_I* user_i;//用户信息开全局 
FLIGHT_I* flight_i;//航班信息开全局 
PASSWORD* password; //读取账号密码 
ADMIN_I* admin_i;//管理员列表 
int main(){
	char user_id[20];
	UID=login(user_id);//实际使用这个登录，测试时候注释掉这行 
	//UID="20181101051";//测试时用这个直接代表登录 
	type=judje(UID);//管理员是1，普通用户是0 
	readall();//读取文件 初始化 
	show(type);//展示对应用户权限面板 
	select(type);//对应用户权限操作面板 
	{//测试函数 
	
	//show(type);
	//readalluser();
	//readallflight();
	//readpassword();
	//readalladmin();
	//showflight();
	//printf("TYPE==%d\n",type);
	//select(type);
	//deleteflight("hangbanhao");
	//deleteuser("20181101052");
	//deletepassword("123"); 
	//saveflight();
	//change_admin("abc"); 
	//saveall();
	//printf("查的是%s",user_i->next->user_id); 
	//
	//deleteadmin("abc"); 
	//readalladmin(); 
	
}
	saveall();
	freeall();
	scanf("%d");

	return 0;
}
int judje(char *userid){
	FILE *fpRead=fopen("./数据文件/sudolist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("登录信息读取失败");
        return 0;
    }
    char ch=getc(fpRead);
   	char sudolist[10][20];//管理员名单
   	int i=0;//管理员个数
	int d=0;//统计长度
	while(ch != EOF)
	{
		if(ch=='*'){
			ch=getc(fpRead);
			sudolist[i][d]='\0';
			i++;
			d=0;
		}
		else{
			sudolist[i][d]=ch;
			d++;
		}
		ch=getc(fpRead);
	 }
	fclose(fpRead);
	//比较账号密码
	int l=0;
	for(l;l<=i;l++){
		if(strcmp(userid,sudolist[l])==0 ){
			//	printf("用户%s为管理员\n",userid);
				return 1;

		}
	}  
	
	//printf("用户%s为普通用户\n",userid);
	return 0;

}
int show(int x){
 	//普通用户
	 if(x==0) {
 		showmain();
	 }
	 else{
	 	showadmin();
	 }
 }
char* login(char* id){
	char userid[20];
	char password[20];
	char compare[30][2][20];
	printf("请输入您的账户ID:");
	scanf("%s",userid);
	printf("请输入您的密码PASSWORD:");
	scanf("%s",password);
	FILE *fpRead=fopen("./数据文件/userpassword.txt","r");
	 if(fpRead==NULL)
    {
    	printf("登录信息读取失败");
        return 0;
    }
    char ch=getc(fpRead);
    int i=0;//账户信息位数
	int a=1;//1账号，2密码
	int b=0;//输入的位数
	while(ch != EOF)
	{
		if(ch=='*'){
			if(a%2==1){
			 	compare[i][0][b]='\0';
			}
			else if(a%2==0){
				compare[i][1][b]='\0';
			}
			//printf("载入数据%s----%s\n",compare[i][0],compare[i][1]);
			b=0;
			a++;
			if(a%2==1){
				ch=getc(fpRead);
				i++;
			}

		} else{
				if(a%2==1){//账号读取
					compare[i][0][b]=ch;
					b++;
				}
				else if(a%2==0){
							//密码读取
					compare[i][1][b]=ch;
					b++;
				}
		}

		ch=getc(fpRead);
	 }
	fclose(fpRead);
	//比较账号密码
	int l=0;
	for(l;l<=i;l++){
		if(strcmp(userid,compare[l][0])==0 ){
			if(strcmp(password,compare[l][1])==0 ){
				printf("登录成功\n",userid);
				//printf("用户%s登录成功",userid);
				strcpy(id,userid);
				return id;
			}
		}
	}

		printf("%s登录失败",userid);
		return 0;

}
int showmain(){
	char a[30];//读取10个数
	FILE *fpRead=fopen("./数据文件/主面板设计.txt","r");
	 if(fpRead==NULL)
    {
    	printf("主面板读取失败");
        return 0;
    }
    /*
	else{
    		printf("主面板读取成功");
	}
	*/
    char ch=getc(fpRead);
	while(ch != EOF)
	{
		putchar(ch);
		ch=getc(fpRead);
	 }
	 fclose(fpRead);
}
int showadmin(){
//管理员面板展示函数
char a[30];//读取10个数
	FILE *fpRead=fopen("./数据文件/管理员面板设计.txt","r");
	 if(fpRead==NULL)
    {
    	printf("主面板读取失败");
        return 0;
    }
    /*
	else{
    		printf("主面板读取成功");
	}
	*/
    char ch=getc(fpRead);
	while(ch != EOF)
	{
		putchar(ch);
		ch=getc(fpRead);
	 }
	 fclose(fpRead);

}

int searchme(char *x){//查询个人信息 

	char string[5][10]={"姓名","性别","电话","身份证号","航班信息"};
	FILE *fpRead=fopen("./数据文件/userlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("信息读取失败");
        return 0;
    }
    else{
	printf("信息读取成功");
	}
    char ID[20];
    int a=0;
    char ch=getc(fpRead);
   	while(ch != EOF)
	{

		if(ch=='-'){
			ID[a]='\0';
			a=0;
			int d=0;
			if(strcmp(x,ID)==0){
				printf("用户%s查找信息成功\n",x);
				char information[5][20];
				int i1=-1,i2=0;
					while(ch!='*'){
						if(ch=='-'){
							i1++;
							i2=0;
						}
						else{
							information[i1][i2]=ch;
							i2++;
							information[i1][i2]='\0';
						}
						ch=getc(fpRead);

				}
				int i3=0;
				for(i3;i3<5;i3++){
					printf("%s:%s\n",string[i3],information[i3]);
				}
				return 1;
			}
			else{
				while(ch!='*'){
					ch=getc(fpRead);
					
				}
				//printf("\n跳过%s数据",ID);
				a=-1;
				ch=getc(fpRead);//吸收回车 
				
			}
		}
		else{
			ID[a]=ch;
		}
		a++;
		ch=getc(fpRead);
	 }
	 printf("\n查询失败\n");
	fclose(fpRead);
	return 0; 


}
int searchflight(char *x){//查询指定航班号信息 
	
	char string[7][20]={"航班起始点","航班终点","飞行时间","预售票总票数","已售票总票数","购票用户","航班编号"};
	FILE *fpRead=fopen("./数据文件/flightlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("信息读取失败");
        return 0;
    }
    else{
	printf("信息读取成功");
	}
    char ID[20];
    int a=0;
    char ch=getc(fpRead);
   	while(ch != EOF)
	{

		if(ch=='-'){

			ID[a]='\0';
			a=0;
			int d=0;
			if(strcmp(x,ID)==0){
				printf("航班%s查找信息成功\n",x);
				char information[7][20];
				int i1=-1,i2=0;
					while(ch!='*'){
						if(ch=='-'){
							i1++;
							i2=0;
						}
						else{
							information[i1][i2]=ch;
							i2++;
							information[i1][i2]='\0';
						}
						ch=getc(fpRead);

				}
				int i3=0;
				printf("%s:----------%s\n",string[6],x);

				for(i3;i3<6;i3++){
					printf("%s:%s\n",string[i3],information[i3]);
				}
				return 1;
			}
			else{
				while(ch!='*'){
					ch=getc(fpRead);
					
				}printf("\n跳过%s数据",ID);
				a=-1;
				ch=getc(fpRead);//吸收回车 
				
			}
		}
		else{
			ID[a]=ch;
		}
		a++;
		ch=getc(fpRead);
	 }
	 printf("\n查询失败\n");
	fclose(fpRead);


}

int showuser(){//展示所有用户 

	USER_I user[30]; 
	
	char str[6][20]={"账号","姓名","性别","联系电话","身份证","预定航班信息"};
	printf("\n%-15s%-10s%-5s%-15s%-15s%-15s",str[0],str[1],str[2],str[3],str[4],str[5]); 
	
	FILE *fpRead=fopen("./数据文件/userlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("信息读取失败");
        return 0;
    }
    else{
//	printf("信息读取成功\n");
	}
    char string[20];//接收字符 
    int n=0;//数字的第N位； 
    int count=0;//读取人数
	int num=0;//读取信息位数 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//文件读取
   	
   		if(ch=='-'||ch=='*'){
   			
   			string[n]='\0';
   			//printf("%s count==%d,num==%d\n",string,count,num);
   			if(num==0){
   				strcpy(user[count].user_id,string);
			   }
			else if(num==1){
				strcpy(user[count].user_name,string);
			}
			else if(num==2){
				strcpy(user[count].user_sex,string);
			}
			else if(num==3){
				strcpy(user[count].user_phonenumber,string);
			}
			else if(num==4){
				strcpy(user[count].user_chinaid,string);
			}
			else if(num==5){
				strcpy(user[count].user_bookinginformation,string);
			}
				
   				num++;
   				num=num%6;
			   n=0;
			   if(ch=='*'){
			   	ch=getc(fpRead);
			   	count++;
			   }
			   else{
			   	ch=getc(fpRead);
			   }
			   continue;
		   }
		   
	    string[n]=ch; 
	    n++;
	    
	    ch=getc(fpRead);
	}
	
	fclose(fpRead);
	//输出读入的信息
	
	int i=0;
	for(i;i<=count;i++){
			printf("\n%-15s%-10s%-5s%-15s%-15s%-15s",user[i].user_id,user[i].user_name,user[i].user_sex,user[i].user_phonenumber,user[i].user_chinaid,user[i].user_bookinginformation); 
	} 
	
	return 0;
} 
int showflight(){//展示所有航班 
	
	/*
	   char flightNo[10];   //航班号
   char start[10];      //起始站
   char end[10];       //终点站
   float day;          //飞行时间
   int  totalTicket;     //预售票总数
   int  sellTicket;      //已售票总数
   int user[FLIGHTMAX];//购票用户账号
	*/
	FLIGHT_I flight[30]; 
	
	char str[6][20]={"航班号","起始站","终点站","飞行时间","预售总数","已售总数"};
	printf("\n%-15s%-10s%-10s%-10s%-15s%-15s",str[0],str[1],str[2],str[3],str[4],str[5]); 
	
	FILE *fpRead=fopen("./数据文件/flightlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("信息读取失败");
        return 0;
    }
    else{
	//	printf("信息读取成功\n");
	}
    char string[30];//接收字符 
    int n=0;//数字的第N位； 
    int count=0;//读取人数
	int num=0;//读取信息位数 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//文件读取
   	//printf("string==%s\n",string);
   		if(ch=='-'||ch=='*'){
   			
   			string[n]='\0';
   			//printf("%s count==%d,num==%d\n",string,count,num);
   			if(num==0){
   				strcpy(flight[count].flightNo,string);
			   }
			else if(num==1){
				strcpy(flight[count].start,string);
			}
			else if(num==2){
				strcpy(flight[count].end,string);
			}
			else if(num==3){
				strcpy(flight[count].day,string);
			}
			else if(num==4){
				strcpy(flight[count].totalTicket,string);
			}
			else if(num==5){
				strcpy(flight[count].sellTicket,string);
			}
			else if(num==6){
				strcpy(flight[count].user[0],string);
			}
				
   				num++;
   				num=num%7;
			   	n=0;
			   if(ch=='*'){
			   	ch=getc(fpRead);
			   	count++;
			   }
			   else{
			   	ch=getc(fpRead);
			   }
			   continue;
		   }
		   
	    string[n]=ch; 
	    n++;
	    
	    ch=getc(fpRead);
	}
	
	fclose(fpRead);
	//输出读入的信息
	
	int i=0;
	for(i;i<=count;i++){
			printf("\n%-15s%-10s%-10s%-10s%-15s%-15s",flight[i].flightNo,flight[i].start,flight[i].end,flight[i].day,flight[i].totalTicket,flight[i].sellTicket); 
	} 
	
	return 0;
	
}
//用户和管理员的选择面板 
int select(int x){
//printf("TYPE==%d\n",x);
	if(x){
		//printf("TYPE==%d\n",x);
		select_admin();
	}
	else{
		select_user();
	}
} 
int select_admin(){
	while(1){
		printf("\n请输入功能代码：");
		int select;
		char search1[20];
		scanf("%d",&select);
		switch(select){
			case 1://查询单个航班
					
					printf("输入要查询的航班ID");
					scanf("%s",search1);
					searchflight(search1); 
					break;			
			case 2://个人预定航班
					break;
			case 3://查询个人信息
					
					printf("输入要查询的用户ID");
					scanf("%s",search1);
					searchme(search1); 
					break;
			case 4://修改个人信息
					break;
			case 5://创建新用户
					adduser(); 
					break;
			case 6://创建新航班
					addflight();
					break;
			case 7://创建新管理员
					addadmin(); 
					break;
			case 0:	
					printf("保存并退出%d\n",select);
					exit(0); 
					break;
			case 9:
					showadmin();
					break;	
					
			default:
					show(type);
					printf("\0输入错误请从新输入");
		}
	
		
	}
}
int select_user(){
	while(1){
		printf("\n请输入功能代码：");
		int select;
		char search1[20];
		scanf("%d",&select);
		switch(select){
			case 0:	
					printf("保存并退出%d\n",select);
					exit(0);
					break;
			case 1://查询航班信息
					printf("输入要查询的航班ID");
					scanf("%s",search1);
					searchflight(search1); 
					break;	
			case 2://航班个人预定 
					
					break;		 
			case 3:searchme(UID); //查询个人信息 
					break;
			case 4://个人信息修改 
					
					break;
			case 9:
					showmain();
					break;
			default:
					show(type);
					printf("\0输入错误请从新输入");
		}
	
		
	}
	   
}

int adduser(){//增加用户 (管理员权限)

	USER_I addu;
	//默认初始化数据避免写入文件时没东西可以写 
	char a[20]="0";
	strcpy(addu.user_bookinginformation,a);
	strcpy(addu.user_chinaid,a);
	strcpy(addu.user_id,a);
	strcpy(addu.user_name,a);
	strcpy(addu.user_password,a);
	strcpy(addu.user_phonenumber,a);
	strcpy(addu.user_sex,a);
	/*
		1.接收写入的账号
		2.检测用户账号是否存在
		3.写入
			3.1打开文件
			3.2a+ 写入文件
			3.3保存退出文件 
		 
	*/
	printf("\n增加的用户账号为：");
	scanf("%s",a);
	//检测账号是否存在 
	printf("%s",a);
	if(searchme(a)){
		printf("用户已存在，写入失败");
		return 0;
	}
	else if(judje(a)){
		printf("当前账户为管理员账户，写入失败");
		return 0;
		
	} 
	else{
		
		strcpy(addu.user_id,a);
		printf("用户不存在，可以创建为新用户\n");
			printf("增加的用户身份证号为：");
			scanf("%s",a);
			strcpy(addu.user_chinaid,a);
			printf("增加的用户姓名为：");
			scanf("%s",a);
			strcpy(addu.user_name,a);
			printf("增加的用户账号密码设置为：");
			scanf("%s",a);
			strcpy(addu.user_password,a);
			printf("增加的用户手机号为：");
			scanf("%s",a);
			strcpy(addu.user_phonenumber,a);
			printf("增加的用户性别为：");
			scanf("%s",a);
			strcpy(addu.user_sex,a);
			printf("增加的用户预定的航班为：（没有请回复0）");
			scanf("%s",a);
			strcpy(addu.user_bookinginformation,a);
			
	}//收集信息 
	/*
	按格式写入文档
	1.userlist.txt文档记录信息(回车账号-名字-性别-电话-身份证-预定航班*) 
	2.password.txt文档记录账户用户名密码 （回车账户*密码*） 
	*/
	FILE *fpRead=fopen("./数据文件/userlist.txt","a");
	 if(fpRead==NULL)
    {
    	printf("登录信息读取失败");
        return 0;
    }
    else{
    	fprintf(fpRead,"\n%s-%s-%s-%s-%s-%s*",addu.user_id,addu.user_name,addu.user_sex,addu.user_phonenumber,addu.user_chinaid,addu.user_bookinginformation); 
	} 
	fclose(fpRead); 
	fpRead=fopen("./数据文件/userpassword.txt","a");
	 if(fpRead==NULL)
    {
    	printf("登录信息读取失败");
        return 0;
    }
    else{
    	fprintf(fpRead,"\n%s*%s*",addu.user_id,addu.user_password); 
	} 
	fclose(fpRead); 
		printf("用户%s创建成功，已保存文件\n",addu.user_id);
	
}

int addadmin(){//增加管理员

	
	char a[20]="0";
	char b[20]="0"; 
	/*
		1.接收写入的账号
		2.检测用户账号是否存在
		3.写入
			3.1打开文件
			3.2a+ 写入文件
			3.3保存退出文件 
		 
	*/
	printf("\n增加的用户账号为：");
	scanf("%s",a);
	//检测账号是否存在 
	printf("%s",a);
	int d=judje(a);
	if(d==1){
		printf("管理员账户已经存在，创建失败"); 
		return 0;
	} 
	else{
		printf("请设置用户密码：");
		scanf("%s",b);
		/*
			1.写入账号密码
			2.写入管理员列表 sudolist.txt 
		*/ 
		FILE *fpRead=fopen("./数据文件/userpassword.txt","a");
		 if(fpRead==NULL)
   			{
    			printf("登录信息读取失败");
    		    return 0;
 			  }
    	else{
    		fprintf(fpRead,"\n%s*%s*",a,b); 
			} 
		fclose(fpRead); 
			fpRead=fopen("./数据文件/sudolist.txt","a");
		 if(fpRead==NULL)
   			{
    			printf("登录信息读取失败");
    		    return 0;
 			  }
    	else{
    		fprintf(fpRead,"\n%s*",a); 
			} 
		fclose(fpRead);
		printf("管理员创建成功");
	}
	
} 

int addflight(){//增加航班 
	FLIGHT_I addu;
	//默认初始化数据避免写入文件时没东西可以写 
	char a[20]="0";
	strcpy(addu.flightNo,a);
	strcpy(addu.start,a);
	strcpy(addu.end,a);
	strcpy(addu.day,a);
	strcpy(addu.totalTicket,a);
	strcpy(addu.sellTicket,a);
	strcpy(addu.user,a);
	/*
		1.接收写入的账号
		2.检测用户账号是否存在
		3.写入
			3.1打开文件
			3.2a+ 写入文件
			3.3保存退出文件 
		 
	*/
	printf("\n增加的航班号为：");
	scanf("%s",a);
	//检测账号是否存在 
	printf("%s",a);
	if(searchme(a)){
		printf("航班已存在，写入失败");
		return 0;
	}
	
	else{
		
		strcpy(addu.flightNo,a);
		printf("航班不存在，可以创建为新航班\n");
			printf("增加的航班起点：");
			scanf("%s",a);
			strcpy(addu.start,a);
			printf("增加的航班终点：");
			scanf("%s",a);
			strcpy(addu.end,a);
			printf("增加的航班时间：（例：19/06/01）");
			scanf("%s",a);
			strcpy(addu.day,a);
			printf("增加的航班预售总票数：");
			scanf("%s",a);
			strcpy(addu.totalTicket,a);
			printf("增加的航班已售票数：(默认为0)");
			scanf("%s",a);
			strcpy(addu.sellTicket,a);
			printf("预定航班的用户账号为：（没有请回复0）");
			scanf("%s",a);
			strcpy(addu.user,a);
			
	}//收集信息 
	/*
	按格式写入文档 
	1.flightlist.txt文档记录信息(ID--起点-终点-时间19/06/01-总票数-已售票数-订票用户*) 
	*/
	FILE *fpRead=fopen("./数据文件/flightlist.txt","a");
	 if(fpRead==NULL)
    {
    	printf("登录信息读取失败");
        return 0;
    }
    else{
    	fprintf(fpRead,"\n%s-%s-%s-%s-%s-%s-%s*",addu.flightNo,addu.start,addu.end,addu.day,addu.totalTicket,addu.sellTicket,addu.user); 
	} 
	fclose(fpRead); 
	
		printf("航班%s创建成功，已保存文件\n",addu.flightNo);

}

 
 
 /*
 	读取重要文件函数 
 */  
 
int readall(void){
	
	readalluser();
	readallflight();
	readalladmin();
	readpassword(); 
	
	printf("用户航班管理员密码读取完毕");
} 
int  readalluser(void){//读取并返回所有用户信息

	user_i = (USER_I*)malloc(sizeof(USER_I));//给链表的头节点分配内存
    user_i->next = NULL;//指向设为空
    FILE* file;
    file = fopen("./数据文件/userlist.txt", "r");//打开信息文件
    if (file == NULL)
    {
        printf("[userlist.txt]打开文件失败!");
        return;
    }
    USER_I* s = user_i;//当前结点
    {
        USER_I*	stu = (USER_I*)malloc(sizeof(USER_I));
        //从文本读入用户信息，存进user中
       /* if (fscanf(file, "%s-%s-%s-%s-%s-%s*",stu->user_id,stu->user_name,stu->user_sex,stu->user_phonenumber,stu->user_chinaid,stu->user_bookinginformation) == EOF)
        {
            //如果读入为EOF，也就说为读入为空，那么刚刚新建的stu就不要了，释放分配的内存
            free(stu);
            break;
        } 
        */
        
        //反正只要读进去写进结构体就成了
		 
        
	FILE *fpRead=fopen("./数据文件/userlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("信息读取失败");
        return 0;
    }
    else{
//	printf("信息读取成功\n");
	}
    char string[20];//接收字符 
    int n=0;//数字的第N位； 
    int count=0;//读取人数
	int num=0;//读取信息位数 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//文件读取
  		/*
		  if(ch=='\n'){
  			ch=getc(fpRead);
		  }
		*/
   	
   		if(ch=='-'||ch=='*'){
   			
   			string[n]='\0';
   			//printf("%s count==%d,num==%d\n",string,count,num);
   			if(string[0]=='\n'){
   				int abc=1;
   				for(abc=1;abc<20;abc++){
   					string[abc-1]=string[abc];
				   }
			   } 
   			if(num==0){
   			//	printf("kaishiduqu\n"); 
   				stu = (USER_I*)malloc(sizeof(USER_I));
   				strcpy(stu->user_id,string);
			   }
			else if(num==1){
				strcpy(stu->user_name,string);
			}
			else if(num==2){
				strcpy(stu->user_sex,string);
			}
			else if(num==3){
				strcpy(stu->user_phonenumber,string);
			}
			else if(num==4){
				strcpy(stu->user_chinaid,string);
			}
			else if(num==5){
				strcpy(stu->user_bookinginformation,string);
				//printf("读入用户%s\n",stu->user_id); 
				 stu->next = NULL;
       			 s->next = stu;//将当前节点和新建的节点链接起来
       			 s = stu;//调整当前节点为新节点
       			 if(ch == EOF){
        			break;
				}	
			}
				
   				num++;
   				num=num%6;
			   n=0;
			   if(ch=='*'){
			   	ch=getc(fpRead);
			   	ch=getc(fpRead);
			   	count++;
			   }
			   else{
			   	ch=getc(fpRead);
			   }
			   continue;
		   }
		   
			//printf("%s-%s-%s-%s-%s-%s*",stu->user_id,stu->user_name,stu->user_sex,stu->user_phonenumber,stu->user_chinaid,stu->user_bookinginformation);  
	    string[n]=ch; 
	    n++;
	    
	    ch=getc(fpRead);
	}
	
	fclose(fpRead);
        
        
        
        
         
        
        
        /*
			测试读入内容 
		**/
		//printf("%s-%s-%s-%s-%s-%s*",stu->user_id,stu->user_name,stu->user_sex,stu->user_phonenumber,stu->user_chinaid,stu->user_bookinginformation);  
       
    }
    fclose(file);
	
	}

int  readallflight(void){//读取并返回所有航班信息

	flight_i = (FLIGHT_I*)malloc(sizeof(FLIGHT_I));//给链表的头节点分配内存
    flight_i->next = NULL;//指向设为空
    FILE* file;
    file = fopen("./数据文件/flightlist.txt", "r");//打开信息文件
    if (file == NULL)
    {
        printf("[flightlist.txt]打开文件失败!");
        return;
    }
    FLIGHT_I* s = flight_i;//当前结点

    {
       FLIGHT_I*	stu = (FLIGHT_I*)malloc(sizeof(FLIGHT_I));
        //从文本读入用户信息，存进user中
       /* if (fscanf(file, "%s-%s-%s-%s-%s-%s*",stu->user_id,stu->user_name,stu->user_sex,stu->user_phonenumber,stu->user_chinaid,stu->user_bookinginformation) == EOF)
        {
            //如果读入为EOF，也就说为读入为空，那么刚刚新建的stu就不要了，释放分配的内存
            free(stu);
            break;
        } 
        */
        
        //反正只要读进去写进结构体就成了
		 
        
	FILE *fpRead=fopen("./数据文件/flightlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("信息读取失败");
        return 0;
    }
    else{
//	printf("信息读取成功\n");
	}
    char string[30];//接收字符 
    int n=0;//数字的第N位； 
    int count=0;//读取人数
	int num=0;//读取信息位数 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//文件读取
   	
   		if(ch=='-'||ch=='*'){
   			
   			string[n]='\0';
   			//printf("%s count==%d,num==%d\n",string,count,num);
   				if(string[0]=='\n'){
   				int abc=1;
   				for(abc=1;abc<20;abc++){
   					string[abc-1]=string[abc];
				   }
			   } 
			   if(string[n-1]=='\n'){
			   	string[n-1]=string[n];
			   }
   			if(num==0){
   				stu = (FLIGHT_I*)malloc(sizeof(FLIGHT_I));
   				strcpy(stu->flightNo,string);
   			//printf("航班号%s 是%s---\n",stu->flightNo,stu->flightNo);
			   }
			else if(num==1){
				strcpy(stu->start,string);
			}
			else if(num==2){
				strcpy(stu->end,string);
			}
			else if(num==3){
				strcpy(stu->day,string);
			}
			else if(num==4){
				strcpy(stu->totalTicket,string);
			}
			else if(num==5){
				strcpy(stu->sellTicket,string);
			}
			else if(num==6){
				strcpy(stu->user,string);
			//	printf("%s-%s-%s-%s-%s-%s-%s*",stu->flightNo,stu->start,stu->end,stu->day,stu->totalTicket,stu->sellTicket,stu->user); 
				 stu->next = NULL;
       			 s->next = stu;//将当前节点和新建的节点链接起来
       			 s = stu;//调整当前节点为新节点
       			 if(ch == EOF){
        			break;
				}	
			}
				
   				num++;
   				num=num%7;
			   n=0;
			   if(ch=='*'){
			   	ch=getc(fpRead);
			   	count++;
			   }
			   else{
			   	ch=getc(fpRead);
			   }
			   continue;
		   }
		   
				//printf("%s-%s-%s-%s-%s-%s-%s*",stu->flightNo,stu->start,stu->end,stu->day,stu->totalTicket,stu->sellTicket,stu->user);  
          string[n]=ch; 
	    n++;
	    
	    ch=getc(fpRead);
	}
	
	fclose(fpRead);
        
        
        
        
         
        
        
        /*
			测试读入内容 
		**/
	//	printf("%s-%s-%s-%s-%s-%s-%s*",stu->flightNo,stu->start,stu->end,stu->day,stu->totalTicket,stu->sellTicket,stu->user);  
       /* stu->next = NULL;
        s->next = stu;//将当前节点和新建的节点链接起来
        s = stu;//调整当前节点为新节点
        if(ch == EOF){
        	break;
		}
		*/
    }
    fclose(file);
    
    if(flight_i->next==NULL){
    	printf("stu 是空的\n");
	} 
    
	
	}

int readalladmin(void){//读取并返回所有管理员信息 
	admin_i = (ADMIN_I*)malloc(sizeof(ADMIN_I));//给链表的头节点分配内存
    admin_i ->next = NULL;//指向设为空
    
    ADMIN_I* s = admin_i;//当前结点
    
        PASSWORD*	stu = (ADMIN_I*)malloc(sizeof(ADMIN_I));
        //从文本读入用户信息，存进user
        //反正只要读进去写进结构体就成了
		 
        
	FILE *fpRead=fopen("./数据文件/sudolist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("信息读取失败");
        return 0;
    }
    else{
	//printf("信息读取成功\n");
	}
    char string[30];//接收字符 
    int n=0;//数字的第N位； 
    int count=0;//读取人数
	int num=0;//读取信息位数 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//文件读取
  	
  	
		   
		   //	重新写一下读取账号*密码*\n的代码 
		   
	
		   if(ch=='*'){
		   	string[n]='\0'; 	n=0;
		   		if(string[0]=='\n'||string[0]=='*'){
   				int abc=1;
   				for(abc=1;abc<20;abc++){
   					string[abc-1]=string[abc];
				   }
			   } 

			   		stu = (PASSWORD*)malloc(sizeof(PASSWORD));

			   			ch=getc(fpRead);//读入行尾的回车 
			    		strcpy(stu->uid,string);
			    		
						//printf("%s \n",stu->uid);  
						stu->next = NULL;
       					s->next = stu;//将当前节点和新建的节点链接起来
       			 		s = stu;//调整当前节点为新节点
       				 
				   } 
			   
		   
		
			
	    string[n]=ch; //一直读字符写入string 
	    n++;
	    //printf("==%c==",ch); 
	    ch=getc(fpRead);
	}
	fclose(fpRead);
}	
int readpassword(void){//读取账号密码 
	password = (PASSWORD*)malloc(sizeof(PASSWORD));//给链表的头节点分配内存
    password->next = NULL;//指向设为空
    
    PASSWORD* s = password;//当前结点
    
        PASSWORD*	stu = (PASSWORD*)malloc(sizeof(PASSWORD));
        //从文本读入用户信息，存进user
        //反正只要读进去写进结构体就成了
		 
        
	FILE *fpRead=fopen("./数据文件/userpassword.txt","r");
	 if(fpRead==NULL)
    {
    	printf("信息读取失败");
        return 0;
    }
    else{
	//printf("信息读取成功\n");
	}
    char string[30];//接收字符 
    int n=0;//数字的第N位； 
    int count=0;//读取人数
	int num=0;//读取信息位数 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//文件读取
  	
  	
		   
		   //	重新写一下读取账号*密码*\n的代码 
		   
	
		   if(ch=='*'){
		   	string[n]='\0'; 
		   		if(string[0]=='\n'||string[0]=='*'){
   				int abc=1;
   				for(abc=1;abc<20;abc++){
   					string[abc-1]=string[abc];
				   }
			   } 
		   	num++;//*号的个数 读取内容应该为账号*密码*回车
			   if(num%2==1){//第一个*号是保存账号 
			   		stu = (PASSWORD*)malloc(sizeof(PASSWORD));
   					strcpy(stu->uid,string);
   					
			   } 
			   else if(num%2==0){//第二个*号保存密码
			   			ch=getc(fpRead);//读入行尾的回车 
			    		strcpy(stu->upassword,string);
			
					//	printf("%s %s\n",stu->uid,stu->upassword);  
						stu->next = NULL;
       					s->next = stu;//将当前节点和新建的节点链接起来
       			 		s = stu;//调整当前节点为新节点
       					 
				   } 
			   n=0;
		   } 
		
			
	    string[n]=ch; //一直读字符写入string 
	    n++;
	    //printf("==%c==",ch); 
	    ch=getc(fpRead);
}
	
	fclose(fpRead);
        
        /*
			测试读入内容 
		**/
		//printf("%s-%s-%s-%s-%s-%s*",stu->user_id,stu->user_name,stu->user_sex,stu->user_phonenumber,stu->user_chinaid,stu->user_bookinginformation);  
       

	
	
		 
} 

	
	
	
	
	
	
int deleteadmin(char* x){//删除管理员
	
	//删sudolistADMIN_I
	printf("正在判断%s\n",x);
	ADMIN_I* stu = admin_i->next;//当前节点
    ADMIN_I* pre = admin_i;//当前节点的父节点
    int isFound = 0;//是否找到用户
    if(stu==NULL){
    	printf("stu 是空的\n");
	} 
	while (stu != NULL)
    {	
		printf("正在判断%s\n",stu->admin_id);
        if (strcmp(stu->admin_id,x) == 0)//判断id是否相同
        {
            pre->next = stu->next;
            free(stu);
            //重写进文件
            isFound = 1;
            break;
        }
        pre = pre->next;
        stu = stu->next;
    }
    if (isFound)
    {
        printf("删除%s用户信息成功!\n",x);
        savesudolist();// 
        deletepassword(x);//删账号密码
    }
    else
    {
        printf("没有找到%s记录!\n",x);
    }
    /*
		删除用户账号密码 
	*/
	
	
	 
	 
}	

int deleteuser(char *x){//删除用户
/*
	前提是程序已经读完了用户内容已经 
	用户信息用链表存储
	只需要
	先断后连
	就相当于删除了用户信息
	最后从新W写入文件 
	
	
	还要删除账号密码文件 
*/

	USER_I* stu = user_i->next;//当前节点
    USER_I* pre = user_i;//当前节点的父节点
    int isFound = 0;//是否找到用户
    if(stu==NULL){
    	printf("stu 是空的\n");
	} 
	while (stu != NULL)
    {	printf("正在判断%s\n",stu->user_id);
        if (strcmp(stu->user_id,x) == 0)//判断id是否相同
        {
            pre->next = stu->next;
            free(stu);
            //重写进文件
            isFound = 1;
            break;
        }
        pre = pre->next;
        stu = stu->next;
    }
    if (isFound)
    {
        printf("删除%s用户信息成功!\n",x);
        saveuser();//重新写入文件 
    }
    else
    {
        printf("没有找到%s记录!\n",x);
    }
    /*
		删除用户账号密码 
	*/
	deletepassword(x);
	savepassword(); 
}

int deleteflight(char *x){//删除航班 
/*
	前提是程序已经读完了航班内容已经 
	用户信息用链表存储
	只需要
	先断后连
	就相当于删除了用户信息
	最后从新W写入文件 
*/

	FLIGHT_I* stu = flight_i->next;//当前节点
    FLIGHT_I* pre = flight_i;//当前节点的父节点
    int isFound = 0;//是否找到航班 
    if(stu==NULL){
    	printf("stu 是空的\n");
	} 
	while (stu != NULL)
    {	printf("正在判断%s\n",stu->flightNo);
        if (strcmp(stu->flightNo,x) == 0)//判断id是否相同
        {
            pre->next = stu->next;
            free(stu);
            //重写进文件
            isFound = 1;
            break;
        }
        pre = pre->next;
        stu = stu->next;
    }
    if (isFound)
    {
        printf("删除%s成功!\n",x);
        saveflight();//重新写入文件 
    }
    else
    {
        printf("没有找到该航班%s记录!\n",x);
    }
}

int deletepassword(char *x){//删除登录账号密码 
	/*
	前提是程序已经读完了密码内容已经 
	用户信息用链表存储
	只需要
	先断后连
	就相当于删除了用户信息
	最后从新W写入文件 
*/
	printf("正在判断%s\n",x);
	PASSWORD* stu = password->next;//当前节点
    PASSWORD* pre = password;//当前节点的父节点
    int isFound = 0;//是否找到航班 
    if(stu==NULL){
    	printf("stu 是空的\n");
	} 
	while (stu != NULL)
    {	printf("正在判断%s\n",stu->uid);
        if (strcmp(stu->uid,x) == 0)//判断id是否相同
        {
            pre->next = stu->next;
            free(stu);
            //重写进文件
            isFound = 1;
            break;
        }
        pre = pre->next;
        stu = stu->next;
    }
    if (isFound)
    {
        printf("删除%s账号密码成功!\n",x);
        savepassword();//重新写入文件 
    }
    else
    {
        printf("没有找到该航班%s记录!\n",x);
    }

}

int saveall(){//保存文件
	saveuser();
	saveflight();
	savesudolist();
	savepassword();
	printf("用户信息|航班信息|管理员信息|密码|已经保存"); 
}

int saveuser(){//保存用户列表 


	USER_I* stu = user_i->next;//当前节点
	USER_I addu=*stu;
	 if(stu==NULL){
    	printf("stu 是空的\n");
	} 
	FILE* file;
   		 file = fopen("./数据文件/修改userlist.txt", "w");//打开信息文件
   		 
   		 int l=0;
	while (stu != NULL)
    {	
		
		
		printf("正在写入%s\n",stu->user_id);
        /**
		 写入文件 
		*/
		 
		 
		 	addu=*stu;
		 	if(l){
		 		fprintf(file,"\n%s-%s-%s-%s-%s-%s*",addu.user_id,addu.user_name,addu.user_sex,addu.user_phonenumber,addu.user_chinaid,addu.user_bookinginformation); 
				 }
		 	else{
		 		fprintf(file,"%s-%s-%s-%s-%s-%s*",addu.user_id,addu.user_name,addu.user_sex,addu.user_phonenumber,addu.user_chinaid,addu.user_bookinginformation); 
				l++;
				 }
			 	
	
        stu = stu->next;
    }
    fclose(file);
	
}
int savesudolist(){//保存管理员列表
 		
	ADMIN_I* stu = admin_i->next;//当前节点
	ADMIN_I addu=*stu;
	 if(stu==NULL){
    	printf("stu 是空的\n");
	} 
	FILE* file;
	printf("开始写入sudolist\n");
   		 file = fopen("./数据文件/修改sudolist.txt", "w");//打开信息文件
   		 
   		 int l=0;
	while (stu != NULL)
    {	
		
		
		printf("正在写入%s\n",stu->admin_id);
        /**
		 写入文件 
		*/
		 
		 
		 	addu=*stu;
		 	if(l){
		 		fprintf(file,"\n%s*",stu->admin_id); 
				 }
		 	else{
		 		fprintf(file,"%s*",stu->admin_id); 
				l++;
				 }
			 	
	
        stu = stu->next;
    }
    fclose(file);
}
int saveflight(){//保存航班信息 


	FLIGHT_I* stu = flight_i->next;//当前节点
	FLIGHT_I addu=*stu;
	 if(stu==NULL){
    	printf("stu 是空的\n");
	} 
	FILE* file;
   		 file = fopen("./数据文件/修改flightlist.txt", "w");//打开信息文件
   		 
   		 int l=0;
	while (stu != NULL)
    {	
		
		
		printf("正在写入%s\n",stu->flightNo);
        /**
		 写入文件 
		*/
		 
		 
		 	addu=*stu;
		 	if(l){
		 		fprintf(file,"\n%s-%s-%s-%s-%s-%s-%s*",stu->flightNo,stu->start,stu->end,stu->day,stu->totalTicket,stu->sellTicket,stu->user); 
				 }
		 	else{
		 		fprintf(file,"%s-%s-%s-%s-%s-%s-%s*",stu->flightNo,stu->start,stu->end,stu->day,stu->totalTicket,stu->sellTicket,stu->user); 
				l++;
				 }
			 	
	
        stu = stu->next;
    }
    fclose(file);
	
} 
int savepassword(){//保存密码信息 
	
	PASSWORD* stu = password->next;//当前节点
	PASSWORD addu=*stu;
	 if(stu==NULL){
    	printf("stu 是空的\n");
	} 
	FILE* file;
   		 file = fopen("./数据文件/修改password.txt", "w");//打开信息文件
   		 
   		 int l=0;
	while (stu != NULL)
    {	
		
		
		printf("正在写入%s\n",stu->uid);
        /**
		 写入文件 
		*/
		 
		 
		 	addu=*stu;
		 	if(l){
		 		fprintf(file,"\n%s*%s*",stu->uid,stu->upassword); 
				 }
		 	else{
		 		fprintf(file,"%s*%s*",stu->uid,stu->upassword); 
				l++;
				 }
			 	
	
        stu = stu->next;
    }
    fclose(file);
}
// 释放内存函数 
void freeall(){
		//printf("开始free\n");
 freeuser_i(user_i);
 freeflight_i(flight_i);
 freepassword(password);
 freeadmin_i(admin_i);
}
void freeuser_i(USER_I*x){
	USER_I* p=x;
	//printf("free 了P-- %s\n",p);
	if(p->next!=NULL){
		USER_I* pre=p->next;	
		while(p->next!=NULL){
			//printf("free 了P-- %s\n",p->user_name);
		free(p);
		p=pre;
		pre=pre->next;
		}
		free(p); 
	}
	else{
		free(p);
	}

} 
void freeflight_i(FLIGHT_I* x){
		FLIGHT_I* p=x;
	if(p->next!=NULL){
		FLIGHT_I* pre=p->next;	
		while(p->next!=NULL){
		//	printf("free 了P-- %s\n",p);
		free(p);
		p=pre;
		pre=pre->next;
		}
		free(p); 
	}
	else{
		free(p);
	}
	
}
void freepassword(PASSWORD* x){
		PASSWORD* p=x;
	if(p->next!=NULL){
		PASSWORD* pre=p->next;	
		while(p->next!=NULL){
		//	printf("free 了P-- %s\n",p->upassword);
		free(p);
		p=pre;
		pre=pre->next;
		}
		free(p); 
	}
	else{
		free(p);
	}
	
	
}
void freeadmin_i(ADMIN_I* x){
	
		ADMIN_I* p=x;
	if(p->next!=NULL){
		ADMIN_I* pre=p->next;	
		while(p->next!=NULL){
		//	printf("free 了P-- %s\n",p);
		free(p);
		p=pre;
		pre=pre->next;
		}
		free(p); 
	}
	else{
		free(p);
	}
	
}
 /*
	修改 
*/
//修改用户资料
int change_user(char* x){
	while(1){
	printf("\n1-修改姓名name\n");
	printf("2-修改性别sex\n");
	printf("3-修改手机号phone\n");
	printf("4-修改身份证号码china-id\n");
	printf("5-修改密码key\n");
	printf("6-修改航班信息flight-information\n");
	printf("0-退出\n");
	printf("请输入修改类型");
	int e;
	scanf("%d",&e);
	if(e==1) {
		change_user_name(x);
	}
	else if(e==2){
		change_user_sex(x);
	}
	else if(e==3){
		change_user_phone(x);
	}
	else if(e==4){
		change_user_chinaid(x);
	}
	else if(e==5){
		change_user_password(x);
	}
	else if(e==6){
		change_user_flight(x);
	}
	else if(e==0){
		return 1;
	}
		
		
	
  }

	
}
int change_user_name(char* x){
	USER_I* u=user_i->next;
	while(u!=NULL){
		if(strcmp(u->user_id,x)==0){
			printf("\n查找到该用户，请输入要修改的姓名");
			char change[20];
			scanf("%s",change);
			strcpy(u->user_name,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->user_name);
		}
		 u=u->next;
	} 
		
		printf("未查找到该用户，修改姓名失败");
	
	return 0;
}
int change_user_sex(char* x){
	USER_I* u=user_i->next;
	while(u!=NULL){
		if(strcmp(u->user_id,x)==0){
			printf("\n查找到该用户，请输入要修改的性别");
			char change[20];
			scanf("%s",change);
			strcpy(u->user_sex,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->user_sex);
		}
		u=u->next;
		 
	} 
	
		printf("未查找到该用户，修改性别失败");
	
	return 0;
} 
int change_user_phone(char* x){
		USER_I* u=user_i->next;
	while(u!=NULL){
		if(strcmp(u->user_id,x)==0){
			printf("\n查找到该用户，请输入要修改的手机号");
			char change[20];
			scanf("%s",change);
			strcpy(u->user_phonenumber,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->user_phonenumber);
		}
		 u=u->next;
	} 
	
		printf("未查找到该用户，修改手机号失败");
	
	return 0;
}
int change_user_chinaid(char* x){
		USER_I* u=user_i->next;
	while(u!=NULL){
		if(strcmp(u->user_id,x)==0){
			printf("\n查找到该用户，请输入要修改的身份证号码");
			char change[20];
			scanf("%s",change);
			strcpy(u->user_chinaid,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->user_chinaid);
		}
		 u=u->next;
	} 
	
		printf("未查找到该用户，修改身份证号码失败");
	
	return 0;
}
int change_user_password(char* x){
			PASSWORD* u=password->next;
	while(u!=NULL){
		if(strcmp(u->uid,x)==0){
			printf("\n查找到该用户，请输入要修改的密码");
			char change[20];
			scanf("%s",change);
			strcpy(u->upassword,change);
			return 1;
		}
		else{
			printf("\n匹配%s 失败",u->uid);
		}
		 u=u->next;
	} 
	
		printf("未查找到该用户，修改密码失败");
	
	return 0;
}
int change_user_flight(char* x){
	USER_I* u=user_i->next;
	while(u!=NULL){
		if(strcmp(u->user_id,x)==0){
			printf("\n查找到该用户，请输入要修改的航班");
			char change[20];
			scanf("%s",change);
			strcpy(u->user_bookinginformation,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->user_bookinginformation);
		}
		 u=u->next;
	} 
	
		printf("未查找到该用户，修改密码失败");
	
	return 0;
}
//修改航班信息


int change_flight(char* x){
	
	
		while(1){
	printf("\n1-修改起点\n");
	printf("2-修改终点\n");
	printf("3-修改时间\n");
	printf("4-修改总票数\n");
	printf("5-修改已售票数\n");
	printf("6-修改订票用户\n");
	printf("0-退出\n");
	printf("请输入修改类型");
	int e;
	scanf("%d",&e);
	if(e==1) {
		change_flight_start(x);
	}
	else if(e==2){
		change_flight_end(x);
	}
	else if(e==3){
		change_flight_day(x);
	}
	else if(e==4){
		change_flight_total(x);
	}
	else if(e==5){
		change_flight_sell(x);
	}
	else if(e==6){
		change_flight_user(x);
	}
	else if(e==0){
		return 1;
	}
		
		
	
  }
	
}
int change_flight_start(char* x){
	
	FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n查找到该航班，请输入要修改的起点");
			char change[20];
			scanf("%s",change);
			strcpy(u->start,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("未查找到该航班，修改起点失败");
	
	return 0;
	
}
int change_flight_end(char* x){
		FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n查找到该航班，请输入要修改的终点");
			char change[20];
			scanf("%s",change);
			strcpy(u->end,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("未查找到该航班，修改终点失败");
	
	return 0;
}
int change_flight_day(char* x){
		FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n查找到该航班，请输入要修改的时间");
			char change[20];
			scanf("%s",change);
			strcpy(u->day,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("未查找到该航班，修改时间失败");
	
	return 0;

} 
int change_flight_total(char* x){
		FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n查找到该航班，请输入要修改的总票数");
			char change[20];
			scanf("%s",change);
			strcpy(u->totalTicket,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("未查找到该航班，修改总票数失败");
	
	return 0;
} 
int change_flight_sell(char* x){
		FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n查找到该航班，请输入要修改的已售票数");
			char change[20];
			scanf("%s",change);
			strcpy(u->sellTicket,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("未查找到该航班，修改已售票数失败");
	
	return 0;
}
int change_flight_user(char* x){
	
		FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n查找到该航班，请输入要修改的购票用户");
			char change[20];
			scanf("%s",change);
			strcpy(u->user,change);
			return 1; 
		}
		else{
			printf("\n匹配%s 失败",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("未查找到该航班，修改购票用户失败");
	
	return 0;
} 


//修改管理员密码
int change_admin(char* x){
	 change_admin_password(x);
}
int change_admin_password(char* x){
	PASSWORD* u=password->next;
	while(u!=NULL){
		if(strcmp(u->uid,x)==0){
			printf("\n查找到该用户，请输入要修改的密码");
			char change[20];
			scanf("%s",change);
			strcpy(u->upassword,change);
			return 1;
		}
		else{
			printf("\n匹配%s 失败",u->uid);
		}
		 u=u->next;
	} 
	
		printf("未查找到该用户，修改密码失败");
	
	return 0;
	
} 
