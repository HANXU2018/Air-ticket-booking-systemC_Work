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
}USER_I;

typedef struct flight_information{
   char flightNo[15];   //航班号
   char start[10];      //起始站
   char end[10];       //终点站
   char day[20];          //飞行时间
   char  totalTicket[10];     //预售票总数
   char  sellTicket[10];      //已售票总数
   char user[FLIGHTMAX][20];//购票用户账号
}FLIGHT_I;  //航班结构体

typedef struct Administrator_information{
	int admin_id;//管理员账号
	char admin_password[20];//密码
} ADMIN_I;

/*基础功能函数
删改使用链表接收所有数据
删改之后从新写入文件 

*/
int select(int x);//选择面板 
int select_user();//用户的选择面板
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
int type; 
char *UID;

/****
主函数
1.登录
2.显示对应角色面板
3.进行角色操作 







**/
int main(){
	char user_id[20];
	UID=login(user_id);//实际使用这个登录，测试时候注释掉这行 
	//UID="20181101051";//测试时用这个直接代表登录 
	type=judje(UID);//管理员是1，普通用户是0 
	show(type);
	//showflight();
	//printf("TYPE==%d\n",type);
	select(type);
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
					 
			case 3:searchme(UID); 
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



