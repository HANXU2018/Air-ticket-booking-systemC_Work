#include<stdio.h>
#include<string.h>
#define IDLEN 13//���֤���볤��
#define FLIGHTMAX 100//�����û��������
#define NAMELEN 10//��������
#define PHONELEN 11//�绰����
#define USERFLIGHTMAX 10//�û����Ԥ����������
#define PASSWORDLEN 10//���볤��


//�������ʹ洢
typedef struct user_information{//�û���Ϣ

	char user_id[15];//�˺�
	char user_name[NAMELEN];//����
	char user_sex[10];//�Ա�
	char user_phonenumber[20];//��ϵ�绰
	char user_chinaid[20];//���֤
	char user_bookinginformation[100];//Ԥ���ĺ�����Ϣ
	char user_password[20];//����
	struct user_information* next;
}USER_I;

typedef struct flight_information{
   char flightNo[15];   //�����
   char start[10];      //��ʼվ
   char end[10];       //�յ�վ
   char day[20];          //����ʱ��
   char  totalTicket[10];     //Ԥ��Ʊ����
   char  sellTicket[10];      //����Ʊ����
   char user[FLIGHTMAX][20];//��Ʊ�û��˺�
   
   struct light_information* next;
}FLIGHT_I;  //����ṹ��

typedef struct Administrator_information{
	char admin_id[20];//����Ա�˺�
	char admin_password[20];//����
	struct Administrator_information* next;
}ADMIN_I;

typedef struct PASSWORD{
	char uid[20];//�˺� 
	char upassword[20];//���� 
	struct PASSWORD* next;
	
}PASSWORD; 

/*�������ܺ���
ɾ��ʹ�����������������
ɾ��֮�����д���ļ� 
*/
/**
	��ȡ�ļ����� 

*/
int readall(void);//��ʼ����ȡʹ���ļ� 
int readalluser(void);//��ȡ�����������û���Ϣ 
int readallflight(void);//��ȡ�����������û���Ϣ
int readalladmin(void);//��ȡ���������й���Ա��Ϣ 
int readpassword(void); //��ȡ�����������˺����� 


int select_admin();//����Աѡ����� 

int showmain();//�û����չʾ����
int showadmin();//����Ա���չʾ����




char* login();//��¼
int judje(char *x);//�ж��û�����
int show(int x);//���չʾ����
/*
	��ѯ 
*/
int searchme(char *x);//�ͻ���ѯ������Ϣ
int searchflight(char *x);//��ѯ������Ϣ
int showuser();//�����û�����
int showflight();//���зɻ����� 

/*
	��� 
*/ 
int adduser();//�����û� 
int addadmin();//���ӹ���Ա
int addflight();//���Ӻ��� 
/*
	�޸� 
*/
//�޸��û�����
int change_user(char* x);
int change_user_name(char* x);
int change_user_sex(char* x);
int change_user_phone(char* x);
int change_user_chinaid(char* x);
int change_user_password(char* x);
int change_user_flight(char* x); 
//�޸ĺ�����Ϣ
int change_flight(char* x); 
int change_flight_start(char* x); 
int change_flight_end(char* x); 
int change_flight_day(char* x); 
int change_flight_total(char* x); 
int change_flight_sell(char* x); 
int change_flight_user(char* x); 
//�޸Ĺ���Ա����
int change_admin(char* x);
int change_admin_password(char* x); 
/*

ɾ������
1.ɾ���û�
2.ɾ������Ա
3.ɾ������ 
*/ 
int deleteuser(char *x);
int deleteadmin(char *x);
int deleteflight(char *x); 
int deletepassword(char *x);
int deleteadmin(char* x); 

/**
 �����ļ�
 1.����ɾ���û����û��б�
 2.����ɾ������󺽰��б� 
*/
int saveall();
int saveuser();
int saveflight(); 
int savesudolist();
int savepassword();

/****
������
1.��¼
2.��ʾ��Ӧ��ɫ���
3.���н�ɫ���� 

**/


/*
	�ͷ��ڴ� 
*/
void freeall();//�ͷ������ڴ� 
void freeuser_i(USER_I*x);
void freeflight_i(FLIGHT_I* x);
void freepassword(PASSWORD* x);
void freeadmin_i(ADMIN_I* x);


//ȫ�ֱ��� 
int type; 
char *UID;
USER_I* user_i;//�û���Ϣ��ȫ�� 
FLIGHT_I* flight_i;//������Ϣ��ȫ�� 
PASSWORD* password; //��ȡ�˺����� 
ADMIN_I* admin_i;//����Ա�б� 
int main(){
	char user_id[20];
	UID=login(user_id);//ʵ��ʹ�������¼������ʱ��ע�͵����� 
	//UID="20181101051";//����ʱ�����ֱ�Ӵ����¼ 
	type=judje(UID);//����Ա��1����ͨ�û���0 
	readall();//��ȡ�ļ� ��ʼ�� 
	show(type);//չʾ��Ӧ�û�Ȩ����� 
	select(type);//��Ӧ�û�Ȩ�޲������ 
	{//���Ժ��� 
	
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
	//printf("�����%s",user_i->next->user_id); 
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
	FILE *fpRead=fopen("./�����ļ�/sudolist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("��¼��Ϣ��ȡʧ��");
        return 0;
    }
    char ch=getc(fpRead);
   	char sudolist[10][20];//����Ա����
   	int i=0;//����Ա����
	int d=0;//ͳ�Ƴ���
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
	//�Ƚ��˺�����
	int l=0;
	for(l;l<=i;l++){
		if(strcmp(userid,sudolist[l])==0 ){
			//	printf("�û�%sΪ����Ա\n",userid);
				return 1;

		}
	}  
	
	//printf("�û�%sΪ��ͨ�û�\n",userid);
	return 0;

}
int show(int x){
 	//��ͨ�û�
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
	printf("�����������˻�ID:");
	scanf("%s",userid);
	printf("��������������PASSWORD:");
	scanf("%s",password);
	FILE *fpRead=fopen("./�����ļ�/userpassword.txt","r");
	 if(fpRead==NULL)
    {
    	printf("��¼��Ϣ��ȡʧ��");
        return 0;
    }
    char ch=getc(fpRead);
    int i=0;//�˻���Ϣλ��
	int a=1;//1�˺ţ�2����
	int b=0;//�����λ��
	while(ch != EOF)
	{
		if(ch=='*'){
			if(a%2==1){
			 	compare[i][0][b]='\0';
			}
			else if(a%2==0){
				compare[i][1][b]='\0';
			}
			//printf("��������%s----%s\n",compare[i][0],compare[i][1]);
			b=0;
			a++;
			if(a%2==1){
				ch=getc(fpRead);
				i++;
			}

		} else{
				if(a%2==1){//�˺Ŷ�ȡ
					compare[i][0][b]=ch;
					b++;
				}
				else if(a%2==0){
							//�����ȡ
					compare[i][1][b]=ch;
					b++;
				}
		}

		ch=getc(fpRead);
	 }
	fclose(fpRead);
	//�Ƚ��˺�����
	int l=0;
	for(l;l<=i;l++){
		if(strcmp(userid,compare[l][0])==0 ){
			if(strcmp(password,compare[l][1])==0 ){
				printf("��¼�ɹ�\n",userid);
				//printf("�û�%s��¼�ɹ�",userid);
				strcpy(id,userid);
				return id;
			}
		}
	}

		printf("%s��¼ʧ��",userid);
		return 0;

}
int showmain(){
	char a[30];//��ȡ10����
	FILE *fpRead=fopen("./�����ļ�/��������.txt","r");
	 if(fpRead==NULL)
    {
    	printf("������ȡʧ��");
        return 0;
    }
    /*
	else{
    		printf("������ȡ�ɹ�");
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
//����Ա���չʾ����
char a[30];//��ȡ10����
	FILE *fpRead=fopen("./�����ļ�/����Ա������.txt","r");
	 if(fpRead==NULL)
    {
    	printf("������ȡʧ��");
        return 0;
    }
    /*
	else{
    		printf("������ȡ�ɹ�");
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

int searchme(char *x){//��ѯ������Ϣ 

	char string[5][10]={"����","�Ա�","�绰","���֤��","������Ϣ"};
	FILE *fpRead=fopen("./�����ļ�/userlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("��Ϣ��ȡʧ��");
        return 0;
    }
    else{
	printf("��Ϣ��ȡ�ɹ�");
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
				printf("�û�%s������Ϣ�ɹ�\n",x);
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
				//printf("\n����%s����",ID);
				a=-1;
				ch=getc(fpRead);//���ջس� 
				
			}
		}
		else{
			ID[a]=ch;
		}
		a++;
		ch=getc(fpRead);
	 }
	 printf("\n��ѯʧ��\n");
	fclose(fpRead);
	return 0; 


}
int searchflight(char *x){//��ѯָ���������Ϣ 
	
	char string[7][20]={"������ʼ��","�����յ�","����ʱ��","Ԥ��Ʊ��Ʊ��","����Ʊ��Ʊ��","��Ʊ�û�","������"};
	FILE *fpRead=fopen("./�����ļ�/flightlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("��Ϣ��ȡʧ��");
        return 0;
    }
    else{
	printf("��Ϣ��ȡ�ɹ�");
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
				printf("����%s������Ϣ�ɹ�\n",x);
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
					
				}printf("\n����%s����",ID);
				a=-1;
				ch=getc(fpRead);//���ջس� 
				
			}
		}
		else{
			ID[a]=ch;
		}
		a++;
		ch=getc(fpRead);
	 }
	 printf("\n��ѯʧ��\n");
	fclose(fpRead);


}

int showuser(){//չʾ�����û� 

	USER_I user[30]; 
	
	char str[6][20]={"�˺�","����","�Ա�","��ϵ�绰","���֤","Ԥ��������Ϣ"};
	printf("\n%-15s%-10s%-5s%-15s%-15s%-15s",str[0],str[1],str[2],str[3],str[4],str[5]); 
	
	FILE *fpRead=fopen("./�����ļ�/userlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("��Ϣ��ȡʧ��");
        return 0;
    }
    else{
//	printf("��Ϣ��ȡ�ɹ�\n");
	}
    char string[20];//�����ַ� 
    int n=0;//���ֵĵ�Nλ�� 
    int count=0;//��ȡ����
	int num=0;//��ȡ��Ϣλ�� 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//�ļ���ȡ
   	
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
	//����������Ϣ
	
	int i=0;
	for(i;i<=count;i++){
			printf("\n%-15s%-10s%-5s%-15s%-15s%-15s",user[i].user_id,user[i].user_name,user[i].user_sex,user[i].user_phonenumber,user[i].user_chinaid,user[i].user_bookinginformation); 
	} 
	
	return 0;
} 
int showflight(){//չʾ���к��� 
	
	/*
	   char flightNo[10];   //�����
   char start[10];      //��ʼվ
   char end[10];       //�յ�վ
   float day;          //����ʱ��
   int  totalTicket;     //Ԥ��Ʊ����
   int  sellTicket;      //����Ʊ����
   int user[FLIGHTMAX];//��Ʊ�û��˺�
	*/
	FLIGHT_I flight[30]; 
	
	char str[6][20]={"�����","��ʼվ","�յ�վ","����ʱ��","Ԥ������","��������"};
	printf("\n%-15s%-10s%-10s%-10s%-15s%-15s",str[0],str[1],str[2],str[3],str[4],str[5]); 
	
	FILE *fpRead=fopen("./�����ļ�/flightlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("��Ϣ��ȡʧ��");
        return 0;
    }
    else{
	//	printf("��Ϣ��ȡ�ɹ�\n");
	}
    char string[30];//�����ַ� 
    int n=0;//���ֵĵ�Nλ�� 
    int count=0;//��ȡ����
	int num=0;//��ȡ��Ϣλ�� 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//�ļ���ȡ
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
	//����������Ϣ
	
	int i=0;
	for(i;i<=count;i++){
			printf("\n%-15s%-10s%-10s%-10s%-15s%-15s",flight[i].flightNo,flight[i].start,flight[i].end,flight[i].day,flight[i].totalTicket,flight[i].sellTicket); 
	} 
	
	return 0;
	
}
//�û��͹���Ա��ѡ����� 
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
		printf("\n�����빦�ܴ��룺");
		int select;
		char search1[20];
		scanf("%d",&select);
		switch(select){
			case 1://��ѯ��������
					
					printf("����Ҫ��ѯ�ĺ���ID");
					scanf("%s",search1);
					searchflight(search1); 
					break;			
			case 2://����Ԥ������
					break;
			case 3://��ѯ������Ϣ
					
					printf("����Ҫ��ѯ���û�ID");
					scanf("%s",search1);
					searchme(search1); 
					break;
			case 4://�޸ĸ�����Ϣ
					break;
			case 5://�������û�
					adduser(); 
					break;
			case 6://�����º���
					addflight();
					break;
			case 7://�����¹���Ա
					addadmin(); 
					break;
			case 0:	
					printf("���沢�˳�%d\n",select);
					exit(0); 
					break;
			case 9:
					showadmin();
					break;	
					
			default:
					show(type);
					printf("\0����������������");
		}
	
		
	}
}
int select_user(){
	while(1){
		printf("\n�����빦�ܴ��룺");
		int select;
		char search1[20];
		scanf("%d",&select);
		switch(select){
			case 0:	
					printf("���沢�˳�%d\n",select);
					exit(0);
					break;
			case 1://��ѯ������Ϣ
					printf("����Ҫ��ѯ�ĺ���ID");
					scanf("%s",search1);
					searchflight(search1); 
					break;	
			case 2://�������Ԥ�� 
					
					break;		 
			case 3:searchme(UID); //��ѯ������Ϣ 
					break;
			case 4://������Ϣ�޸� 
					
					break;
			case 9:
					showmain();
					break;
			default:
					show(type);
					printf("\0����������������");
		}
	
		
	}
	   
}

int adduser(){//�����û� (����ԱȨ��)

	USER_I addu;
	//Ĭ�ϳ�ʼ�����ݱ���д���ļ�ʱû��������д 
	char a[20]="0";
	strcpy(addu.user_bookinginformation,a);
	strcpy(addu.user_chinaid,a);
	strcpy(addu.user_id,a);
	strcpy(addu.user_name,a);
	strcpy(addu.user_password,a);
	strcpy(addu.user_phonenumber,a);
	strcpy(addu.user_sex,a);
	/*
		1.����д����˺�
		2.����û��˺��Ƿ����
		3.д��
			3.1���ļ�
			3.2a+ д���ļ�
			3.3�����˳��ļ� 
		 
	*/
	printf("\n���ӵ��û��˺�Ϊ��");
	scanf("%s",a);
	//����˺��Ƿ���� 
	printf("%s",a);
	if(searchme(a)){
		printf("�û��Ѵ��ڣ�д��ʧ��");
		return 0;
	}
	else if(judje(a)){
		printf("��ǰ�˻�Ϊ����Ա�˻���д��ʧ��");
		return 0;
		
	} 
	else{
		
		strcpy(addu.user_id,a);
		printf("�û������ڣ����Դ���Ϊ���û�\n");
			printf("���ӵ��û����֤��Ϊ��");
			scanf("%s",a);
			strcpy(addu.user_chinaid,a);
			printf("���ӵ��û�����Ϊ��");
			scanf("%s",a);
			strcpy(addu.user_name,a);
			printf("���ӵ��û��˺���������Ϊ��");
			scanf("%s",a);
			strcpy(addu.user_password,a);
			printf("���ӵ��û��ֻ���Ϊ��");
			scanf("%s",a);
			strcpy(addu.user_phonenumber,a);
			printf("���ӵ��û��Ա�Ϊ��");
			scanf("%s",a);
			strcpy(addu.user_sex,a);
			printf("���ӵ��û�Ԥ���ĺ���Ϊ����û����ظ�0��");
			scanf("%s",a);
			strcpy(addu.user_bookinginformation,a);
			
	}//�ռ���Ϣ 
	/*
	����ʽд���ĵ�
	1.userlist.txt�ĵ���¼��Ϣ(�س��˺�-����-�Ա�-�绰-���֤-Ԥ������*) 
	2.password.txt�ĵ���¼�˻��û������� ���س��˻�*����*�� 
	*/
	FILE *fpRead=fopen("./�����ļ�/userlist.txt","a");
	 if(fpRead==NULL)
    {
    	printf("��¼��Ϣ��ȡʧ��");
        return 0;
    }
    else{
    	fprintf(fpRead,"\n%s-%s-%s-%s-%s-%s*",addu.user_id,addu.user_name,addu.user_sex,addu.user_phonenumber,addu.user_chinaid,addu.user_bookinginformation); 
	} 
	fclose(fpRead); 
	fpRead=fopen("./�����ļ�/userpassword.txt","a");
	 if(fpRead==NULL)
    {
    	printf("��¼��Ϣ��ȡʧ��");
        return 0;
    }
    else{
    	fprintf(fpRead,"\n%s*%s*",addu.user_id,addu.user_password); 
	} 
	fclose(fpRead); 
		printf("�û�%s�����ɹ����ѱ����ļ�\n",addu.user_id);
	
}

int addadmin(){//���ӹ���Ա

	
	char a[20]="0";
	char b[20]="0"; 
	/*
		1.����д����˺�
		2.����û��˺��Ƿ����
		3.д��
			3.1���ļ�
			3.2a+ д���ļ�
			3.3�����˳��ļ� 
		 
	*/
	printf("\n���ӵ��û��˺�Ϊ��");
	scanf("%s",a);
	//����˺��Ƿ���� 
	printf("%s",a);
	int d=judje(a);
	if(d==1){
		printf("����Ա�˻��Ѿ����ڣ�����ʧ��"); 
		return 0;
	} 
	else{
		printf("�������û����룺");
		scanf("%s",b);
		/*
			1.д���˺�����
			2.д�����Ա�б� sudolist.txt 
		*/ 
		FILE *fpRead=fopen("./�����ļ�/userpassword.txt","a");
		 if(fpRead==NULL)
   			{
    			printf("��¼��Ϣ��ȡʧ��");
    		    return 0;
 			  }
    	else{
    		fprintf(fpRead,"\n%s*%s*",a,b); 
			} 
		fclose(fpRead); 
			fpRead=fopen("./�����ļ�/sudolist.txt","a");
		 if(fpRead==NULL)
   			{
    			printf("��¼��Ϣ��ȡʧ��");
    		    return 0;
 			  }
    	else{
    		fprintf(fpRead,"\n%s*",a); 
			} 
		fclose(fpRead);
		printf("����Ա�����ɹ�");
	}
	
} 

int addflight(){//���Ӻ��� 
	FLIGHT_I addu;
	//Ĭ�ϳ�ʼ�����ݱ���д���ļ�ʱû��������д 
	char a[20]="0";
	strcpy(addu.flightNo,a);
	strcpy(addu.start,a);
	strcpy(addu.end,a);
	strcpy(addu.day,a);
	strcpy(addu.totalTicket,a);
	strcpy(addu.sellTicket,a);
	strcpy(addu.user,a);
	/*
		1.����д����˺�
		2.����û��˺��Ƿ����
		3.д��
			3.1���ļ�
			3.2a+ д���ļ�
			3.3�����˳��ļ� 
		 
	*/
	printf("\n���ӵĺ����Ϊ��");
	scanf("%s",a);
	//����˺��Ƿ���� 
	printf("%s",a);
	if(searchme(a)){
		printf("�����Ѵ��ڣ�д��ʧ��");
		return 0;
	}
	
	else{
		
		strcpy(addu.flightNo,a);
		printf("���಻���ڣ����Դ���Ϊ�º���\n");
			printf("���ӵĺ�����㣺");
			scanf("%s",a);
			strcpy(addu.start,a);
			printf("���ӵĺ����յ㣺");
			scanf("%s",a);
			strcpy(addu.end,a);
			printf("���ӵĺ���ʱ�䣺������19/06/01��");
			scanf("%s",a);
			strcpy(addu.day,a);
			printf("���ӵĺ���Ԥ����Ʊ����");
			scanf("%s",a);
			strcpy(addu.totalTicket,a);
			printf("���ӵĺ�������Ʊ����(Ĭ��Ϊ0)");
			scanf("%s",a);
			strcpy(addu.sellTicket,a);
			printf("Ԥ��������û��˺�Ϊ����û����ظ�0��");
			scanf("%s",a);
			strcpy(addu.user,a);
			
	}//�ռ���Ϣ 
	/*
	����ʽд���ĵ� 
	1.flightlist.txt�ĵ���¼��Ϣ(ID--���-�յ�-ʱ��19/06/01-��Ʊ��-����Ʊ��-��Ʊ�û�*) 
	*/
	FILE *fpRead=fopen("./�����ļ�/flightlist.txt","a");
	 if(fpRead==NULL)
    {
    	printf("��¼��Ϣ��ȡʧ��");
        return 0;
    }
    else{
    	fprintf(fpRead,"\n%s-%s-%s-%s-%s-%s-%s*",addu.flightNo,addu.start,addu.end,addu.day,addu.totalTicket,addu.sellTicket,addu.user); 
	} 
	fclose(fpRead); 
	
		printf("����%s�����ɹ����ѱ����ļ�\n",addu.flightNo);

}

 
 
 /*
 	��ȡ��Ҫ�ļ����� 
 */  
 
int readall(void){
	
	readalluser();
	readallflight();
	readalladmin();
	readpassword(); 
	
	printf("�û��������Ա�����ȡ���");
} 
int  readalluser(void){//��ȡ�����������û���Ϣ

	user_i = (USER_I*)malloc(sizeof(USER_I));//�������ͷ�ڵ�����ڴ�
    user_i->next = NULL;//ָ����Ϊ��
    FILE* file;
    file = fopen("./�����ļ�/userlist.txt", "r");//����Ϣ�ļ�
    if (file == NULL)
    {
        printf("[userlist.txt]���ļ�ʧ��!");
        return;
    }
    USER_I* s = user_i;//��ǰ���
    {
        USER_I*	stu = (USER_I*)malloc(sizeof(USER_I));
        //���ı������û���Ϣ�����user��
       /* if (fscanf(file, "%s-%s-%s-%s-%s-%s*",stu->user_id,stu->user_name,stu->user_sex,stu->user_phonenumber,stu->user_chinaid,stu->user_bookinginformation) == EOF)
        {
            //�������ΪEOF��Ҳ��˵Ϊ����Ϊ�գ���ô�ո��½���stu�Ͳ�Ҫ�ˣ��ͷŷ�����ڴ�
            free(stu);
            break;
        } 
        */
        
        //����ֻҪ����ȥд���ṹ��ͳ���
		 
        
	FILE *fpRead=fopen("./�����ļ�/userlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("��Ϣ��ȡʧ��");
        return 0;
    }
    else{
//	printf("��Ϣ��ȡ�ɹ�\n");
	}
    char string[20];//�����ַ� 
    int n=0;//���ֵĵ�Nλ�� 
    int count=0;//��ȡ����
	int num=0;//��ȡ��Ϣλ�� 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//�ļ���ȡ
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
				//printf("�����û�%s\n",stu->user_id); 
				 stu->next = NULL;
       			 s->next = stu;//����ǰ�ڵ���½��Ľڵ���������
       			 s = stu;//������ǰ�ڵ�Ϊ�½ڵ�
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
			���Զ������� 
		**/
		//printf("%s-%s-%s-%s-%s-%s*",stu->user_id,stu->user_name,stu->user_sex,stu->user_phonenumber,stu->user_chinaid,stu->user_bookinginformation);  
       
    }
    fclose(file);
	
	}

int  readallflight(void){//��ȡ���������к�����Ϣ

	flight_i = (FLIGHT_I*)malloc(sizeof(FLIGHT_I));//�������ͷ�ڵ�����ڴ�
    flight_i->next = NULL;//ָ����Ϊ��
    FILE* file;
    file = fopen("./�����ļ�/flightlist.txt", "r");//����Ϣ�ļ�
    if (file == NULL)
    {
        printf("[flightlist.txt]���ļ�ʧ��!");
        return;
    }
    FLIGHT_I* s = flight_i;//��ǰ���

    {
       FLIGHT_I*	stu = (FLIGHT_I*)malloc(sizeof(FLIGHT_I));
        //���ı������û���Ϣ�����user��
       /* if (fscanf(file, "%s-%s-%s-%s-%s-%s*",stu->user_id,stu->user_name,stu->user_sex,stu->user_phonenumber,stu->user_chinaid,stu->user_bookinginformation) == EOF)
        {
            //�������ΪEOF��Ҳ��˵Ϊ����Ϊ�գ���ô�ո��½���stu�Ͳ�Ҫ�ˣ��ͷŷ�����ڴ�
            free(stu);
            break;
        } 
        */
        
        //����ֻҪ����ȥд���ṹ��ͳ���
		 
        
	FILE *fpRead=fopen("./�����ļ�/flightlist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("��Ϣ��ȡʧ��");
        return 0;
    }
    else{
//	printf("��Ϣ��ȡ�ɹ�\n");
	}
    char string[30];//�����ַ� 
    int n=0;//���ֵĵ�Nλ�� 
    int count=0;//��ȡ����
	int num=0;//��ȡ��Ϣλ�� 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//�ļ���ȡ
   	
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
   			//printf("�����%s ��%s---\n",stu->flightNo,stu->flightNo);
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
       			 s->next = stu;//����ǰ�ڵ���½��Ľڵ���������
       			 s = stu;//������ǰ�ڵ�Ϊ�½ڵ�
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
			���Զ������� 
		**/
	//	printf("%s-%s-%s-%s-%s-%s-%s*",stu->flightNo,stu->start,stu->end,stu->day,stu->totalTicket,stu->sellTicket,stu->user);  
       /* stu->next = NULL;
        s->next = stu;//����ǰ�ڵ���½��Ľڵ���������
        s = stu;//������ǰ�ڵ�Ϊ�½ڵ�
        if(ch == EOF){
        	break;
		}
		*/
    }
    fclose(file);
    
    if(flight_i->next==NULL){
    	printf("stu �ǿյ�\n");
	} 
    
	
	}

int readalladmin(void){//��ȡ���������й���Ա��Ϣ 
	admin_i = (ADMIN_I*)malloc(sizeof(ADMIN_I));//�������ͷ�ڵ�����ڴ�
    admin_i ->next = NULL;//ָ����Ϊ��
    
    ADMIN_I* s = admin_i;//��ǰ���
    
        PASSWORD*	stu = (ADMIN_I*)malloc(sizeof(ADMIN_I));
        //���ı������û���Ϣ�����user
        //����ֻҪ����ȥд���ṹ��ͳ���
		 
        
	FILE *fpRead=fopen("./�����ļ�/sudolist.txt","r");
	 if(fpRead==NULL)
    {
    	printf("��Ϣ��ȡʧ��");
        return 0;
    }
    else{
	//printf("��Ϣ��ȡ�ɹ�\n");
	}
    char string[30];//�����ַ� 
    int n=0;//���ֵĵ�Nλ�� 
    int count=0;//��ȡ����
	int num=0;//��ȡ��Ϣλ�� 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//�ļ���ȡ
  	
  	
		   
		   //	����дһ�¶�ȡ�˺�*����*\n�Ĵ��� 
		   
	
		   if(ch=='*'){
		   	string[n]='\0'; 	n=0;
		   		if(string[0]=='\n'||string[0]=='*'){
   				int abc=1;
   				for(abc=1;abc<20;abc++){
   					string[abc-1]=string[abc];
				   }
			   } 

			   		stu = (PASSWORD*)malloc(sizeof(PASSWORD));

			   			ch=getc(fpRead);//������β�Ļس� 
			    		strcpy(stu->uid,string);
			    		
						//printf("%s \n",stu->uid);  
						stu->next = NULL;
       					s->next = stu;//����ǰ�ڵ���½��Ľڵ���������
       			 		s = stu;//������ǰ�ڵ�Ϊ�½ڵ�
       				 
				   } 
			   
		   
		
			
	    string[n]=ch; //һֱ���ַ�д��string 
	    n++;
	    //printf("==%c==",ch); 
	    ch=getc(fpRead);
	}
	fclose(fpRead);
}	
int readpassword(void){//��ȡ�˺����� 
	password = (PASSWORD*)malloc(sizeof(PASSWORD));//�������ͷ�ڵ�����ڴ�
    password->next = NULL;//ָ����Ϊ��
    
    PASSWORD* s = password;//��ǰ���
    
        PASSWORD*	stu = (PASSWORD*)malloc(sizeof(PASSWORD));
        //���ı������û���Ϣ�����user
        //����ֻҪ����ȥд���ṹ��ͳ���
		 
        
	FILE *fpRead=fopen("./�����ļ�/userpassword.txt","r");
	 if(fpRead==NULL)
    {
    	printf("��Ϣ��ȡʧ��");
        return 0;
    }
    else{
	//printf("��Ϣ��ȡ�ɹ�\n");
	}
    char string[30];//�����ַ� 
    int n=0;//���ֵĵ�Nλ�� 
    int count=0;//��ȡ����
	int num=0;//��ȡ��Ϣλ�� 
    char ch=getc(fpRead);
    
  	while(ch != EOF){//�ļ���ȡ
  	
  	
		   
		   //	����дһ�¶�ȡ�˺�*����*\n�Ĵ��� 
		   
	
		   if(ch=='*'){
		   	string[n]='\0'; 
		   		if(string[0]=='\n'||string[0]=='*'){
   				int abc=1;
   				for(abc=1;abc<20;abc++){
   					string[abc-1]=string[abc];
				   }
			   } 
		   	num++;//*�ŵĸ��� ��ȡ����Ӧ��Ϊ�˺�*����*�س�
			   if(num%2==1){//��һ��*���Ǳ����˺� 
			   		stu = (PASSWORD*)malloc(sizeof(PASSWORD));
   					strcpy(stu->uid,string);
   					
			   } 
			   else if(num%2==0){//�ڶ���*�ű�������
			   			ch=getc(fpRead);//������β�Ļس� 
			    		strcpy(stu->upassword,string);
			
					//	printf("%s %s\n",stu->uid,stu->upassword);  
						stu->next = NULL;
       					s->next = stu;//����ǰ�ڵ���½��Ľڵ���������
       			 		s = stu;//������ǰ�ڵ�Ϊ�½ڵ�
       					 
				   } 
			   n=0;
		   } 
		
			
	    string[n]=ch; //һֱ���ַ�д��string 
	    n++;
	    //printf("==%c==",ch); 
	    ch=getc(fpRead);
}
	
	fclose(fpRead);
        
        /*
			���Զ������� 
		**/
		//printf("%s-%s-%s-%s-%s-%s*",stu->user_id,stu->user_name,stu->user_sex,stu->user_phonenumber,stu->user_chinaid,stu->user_bookinginformation);  
       

	
	
		 
} 

	
	
	
	
	
	
int deleteadmin(char* x){//ɾ������Ա
	
	//ɾsudolistADMIN_I
	printf("�����ж�%s\n",x);
	ADMIN_I* stu = admin_i->next;//��ǰ�ڵ�
    ADMIN_I* pre = admin_i;//��ǰ�ڵ�ĸ��ڵ�
    int isFound = 0;//�Ƿ��ҵ��û�
    if(stu==NULL){
    	printf("stu �ǿյ�\n");
	} 
	while (stu != NULL)
    {	
		printf("�����ж�%s\n",stu->admin_id);
        if (strcmp(stu->admin_id,x) == 0)//�ж�id�Ƿ���ͬ
        {
            pre->next = stu->next;
            free(stu);
            //��д���ļ�
            isFound = 1;
            break;
        }
        pre = pre->next;
        stu = stu->next;
    }
    if (isFound)
    {
        printf("ɾ��%s�û���Ϣ�ɹ�!\n",x);
        savesudolist();// 
        deletepassword(x);//ɾ�˺�����
    }
    else
    {
        printf("û���ҵ�%s��¼!\n",x);
    }
    /*
		ɾ���û��˺����� 
	*/
	
	
	 
	 
}	

int deleteuser(char *x){//ɾ���û�
/*
	ǰ���ǳ����Ѿ��������û������Ѿ� 
	�û���Ϣ������洢
	ֻ��Ҫ
	�ȶϺ���
	���൱��ɾ�����û���Ϣ
	������Wд���ļ� 
	
	
	��Ҫɾ���˺������ļ� 
*/

	USER_I* stu = user_i->next;//��ǰ�ڵ�
    USER_I* pre = user_i;//��ǰ�ڵ�ĸ��ڵ�
    int isFound = 0;//�Ƿ��ҵ��û�
    if(stu==NULL){
    	printf("stu �ǿյ�\n");
	} 
	while (stu != NULL)
    {	printf("�����ж�%s\n",stu->user_id);
        if (strcmp(stu->user_id,x) == 0)//�ж�id�Ƿ���ͬ
        {
            pre->next = stu->next;
            free(stu);
            //��д���ļ�
            isFound = 1;
            break;
        }
        pre = pre->next;
        stu = stu->next;
    }
    if (isFound)
    {
        printf("ɾ��%s�û���Ϣ�ɹ�!\n",x);
        saveuser();//����д���ļ� 
    }
    else
    {
        printf("û���ҵ�%s��¼!\n",x);
    }
    /*
		ɾ���û��˺����� 
	*/
	deletepassword(x);
	savepassword(); 
}

int deleteflight(char *x){//ɾ������ 
/*
	ǰ���ǳ����Ѿ������˺��������Ѿ� 
	�û���Ϣ������洢
	ֻ��Ҫ
	�ȶϺ���
	���൱��ɾ�����û���Ϣ
	������Wд���ļ� 
*/

	FLIGHT_I* stu = flight_i->next;//��ǰ�ڵ�
    FLIGHT_I* pre = flight_i;//��ǰ�ڵ�ĸ��ڵ�
    int isFound = 0;//�Ƿ��ҵ����� 
    if(stu==NULL){
    	printf("stu �ǿյ�\n");
	} 
	while (stu != NULL)
    {	printf("�����ж�%s\n",stu->flightNo);
        if (strcmp(stu->flightNo,x) == 0)//�ж�id�Ƿ���ͬ
        {
            pre->next = stu->next;
            free(stu);
            //��д���ļ�
            isFound = 1;
            break;
        }
        pre = pre->next;
        stu = stu->next;
    }
    if (isFound)
    {
        printf("ɾ��%s�ɹ�!\n",x);
        saveflight();//����д���ļ� 
    }
    else
    {
        printf("û���ҵ��ú���%s��¼!\n",x);
    }
}

int deletepassword(char *x){//ɾ����¼�˺����� 
	/*
	ǰ���ǳ����Ѿ����������������Ѿ� 
	�û���Ϣ������洢
	ֻ��Ҫ
	�ȶϺ���
	���൱��ɾ�����û���Ϣ
	������Wд���ļ� 
*/
	printf("�����ж�%s\n",x);
	PASSWORD* stu = password->next;//��ǰ�ڵ�
    PASSWORD* pre = password;//��ǰ�ڵ�ĸ��ڵ�
    int isFound = 0;//�Ƿ��ҵ����� 
    if(stu==NULL){
    	printf("stu �ǿյ�\n");
	} 
	while (stu != NULL)
    {	printf("�����ж�%s\n",stu->uid);
        if (strcmp(stu->uid,x) == 0)//�ж�id�Ƿ���ͬ
        {
            pre->next = stu->next;
            free(stu);
            //��д���ļ�
            isFound = 1;
            break;
        }
        pre = pre->next;
        stu = stu->next;
    }
    if (isFound)
    {
        printf("ɾ��%s�˺�����ɹ�!\n",x);
        savepassword();//����д���ļ� 
    }
    else
    {
        printf("û���ҵ��ú���%s��¼!\n",x);
    }

}

int saveall(){//�����ļ�
	saveuser();
	saveflight();
	savesudolist();
	savepassword();
	printf("�û���Ϣ|������Ϣ|����Ա��Ϣ|����|�Ѿ�����"); 
}

int saveuser(){//�����û��б� 


	USER_I* stu = user_i->next;//��ǰ�ڵ�
	USER_I addu=*stu;
	 if(stu==NULL){
    	printf("stu �ǿյ�\n");
	} 
	FILE* file;
   		 file = fopen("./�����ļ�/�޸�userlist.txt", "w");//����Ϣ�ļ�
   		 
   		 int l=0;
	while (stu != NULL)
    {	
		
		
		printf("����д��%s\n",stu->user_id);
        /**
		 д���ļ� 
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
int savesudolist(){//�������Ա�б�
 		
	ADMIN_I* stu = admin_i->next;//��ǰ�ڵ�
	ADMIN_I addu=*stu;
	 if(stu==NULL){
    	printf("stu �ǿյ�\n");
	} 
	FILE* file;
	printf("��ʼд��sudolist\n");
   		 file = fopen("./�����ļ�/�޸�sudolist.txt", "w");//����Ϣ�ļ�
   		 
   		 int l=0;
	while (stu != NULL)
    {	
		
		
		printf("����д��%s\n",stu->admin_id);
        /**
		 д���ļ� 
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
int saveflight(){//���溽����Ϣ 


	FLIGHT_I* stu = flight_i->next;//��ǰ�ڵ�
	FLIGHT_I addu=*stu;
	 if(stu==NULL){
    	printf("stu �ǿյ�\n");
	} 
	FILE* file;
   		 file = fopen("./�����ļ�/�޸�flightlist.txt", "w");//����Ϣ�ļ�
   		 
   		 int l=0;
	while (stu != NULL)
    {	
		
		
		printf("����д��%s\n",stu->flightNo);
        /**
		 д���ļ� 
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
int savepassword(){//����������Ϣ 
	
	PASSWORD* stu = password->next;//��ǰ�ڵ�
	PASSWORD addu=*stu;
	 if(stu==NULL){
    	printf("stu �ǿյ�\n");
	} 
	FILE* file;
   		 file = fopen("./�����ļ�/�޸�password.txt", "w");//����Ϣ�ļ�
   		 
   		 int l=0;
	while (stu != NULL)
    {	
		
		
		printf("����д��%s\n",stu->uid);
        /**
		 д���ļ� 
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
// �ͷ��ڴ溯�� 
void freeall(){
		//printf("��ʼfree\n");
 freeuser_i(user_i);
 freeflight_i(flight_i);
 freepassword(password);
 freeadmin_i(admin_i);
}
void freeuser_i(USER_I*x){
	USER_I* p=x;
	//printf("free ��P-- %s\n",p);
	if(p->next!=NULL){
		USER_I* pre=p->next;	
		while(p->next!=NULL){
			//printf("free ��P-- %s\n",p->user_name);
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
		//	printf("free ��P-- %s\n",p);
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
		//	printf("free ��P-- %s\n",p->upassword);
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
		//	printf("free ��P-- %s\n",p);
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
	�޸� 
*/
//�޸��û�����
int change_user(char* x){
	while(1){
	printf("\n1-�޸�����name\n");
	printf("2-�޸��Ա�sex\n");
	printf("3-�޸��ֻ���phone\n");
	printf("4-�޸����֤����china-id\n");
	printf("5-�޸�����key\n");
	printf("6-�޸ĺ�����Ϣflight-information\n");
	printf("0-�˳�\n");
	printf("�������޸�����");
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
			printf("\n���ҵ����û���������Ҫ�޸ĵ�����");
			char change[20];
			scanf("%s",change);
			strcpy(u->user_name,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->user_name);
		}
		 u=u->next;
	} 
		
		printf("δ���ҵ����û����޸�����ʧ��");
	
	return 0;
}
int change_user_sex(char* x){
	USER_I* u=user_i->next;
	while(u!=NULL){
		if(strcmp(u->user_id,x)==0){
			printf("\n���ҵ����û���������Ҫ�޸ĵ��Ա�");
			char change[20];
			scanf("%s",change);
			strcpy(u->user_sex,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->user_sex);
		}
		u=u->next;
		 
	} 
	
		printf("δ���ҵ����û����޸��Ա�ʧ��");
	
	return 0;
} 
int change_user_phone(char* x){
		USER_I* u=user_i->next;
	while(u!=NULL){
		if(strcmp(u->user_id,x)==0){
			printf("\n���ҵ����û���������Ҫ�޸ĵ��ֻ���");
			char change[20];
			scanf("%s",change);
			strcpy(u->user_phonenumber,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->user_phonenumber);
		}
		 u=u->next;
	} 
	
		printf("δ���ҵ����û����޸��ֻ���ʧ��");
	
	return 0;
}
int change_user_chinaid(char* x){
		USER_I* u=user_i->next;
	while(u!=NULL){
		if(strcmp(u->user_id,x)==0){
			printf("\n���ҵ����û���������Ҫ�޸ĵ����֤����");
			char change[20];
			scanf("%s",change);
			strcpy(u->user_chinaid,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->user_chinaid);
		}
		 u=u->next;
	} 
	
		printf("δ���ҵ����û����޸����֤����ʧ��");
	
	return 0;
}
int change_user_password(char* x){
			PASSWORD* u=password->next;
	while(u!=NULL){
		if(strcmp(u->uid,x)==0){
			printf("\n���ҵ����û���������Ҫ�޸ĵ�����");
			char change[20];
			scanf("%s",change);
			strcpy(u->upassword,change);
			return 1;
		}
		else{
			printf("\nƥ��%s ʧ��",u->uid);
		}
		 u=u->next;
	} 
	
		printf("δ���ҵ����û����޸�����ʧ��");
	
	return 0;
}
int change_user_flight(char* x){
	USER_I* u=user_i->next;
	while(u!=NULL){
		if(strcmp(u->user_id,x)==0){
			printf("\n���ҵ����û���������Ҫ�޸ĵĺ���");
			char change[20];
			scanf("%s",change);
			strcpy(u->user_bookinginformation,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->user_bookinginformation);
		}
		 u=u->next;
	} 
	
		printf("δ���ҵ����û����޸�����ʧ��");
	
	return 0;
}
//�޸ĺ�����Ϣ


int change_flight(char* x){
	
	
		while(1){
	printf("\n1-�޸����\n");
	printf("2-�޸��յ�\n");
	printf("3-�޸�ʱ��\n");
	printf("4-�޸���Ʊ��\n");
	printf("5-�޸�����Ʊ��\n");
	printf("6-�޸Ķ�Ʊ�û�\n");
	printf("0-�˳�\n");
	printf("�������޸�����");
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
			printf("\n���ҵ��ú��࣬������Ҫ�޸ĵ����");
			char change[20];
			scanf("%s",change);
			strcpy(u->start,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("δ���ҵ��ú��࣬�޸����ʧ��");
	
	return 0;
	
}
int change_flight_end(char* x){
		FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n���ҵ��ú��࣬������Ҫ�޸ĵ��յ�");
			char change[20];
			scanf("%s",change);
			strcpy(u->end,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("δ���ҵ��ú��࣬�޸��յ�ʧ��");
	
	return 0;
}
int change_flight_day(char* x){
		FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n���ҵ��ú��࣬������Ҫ�޸ĵ�ʱ��");
			char change[20];
			scanf("%s",change);
			strcpy(u->day,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("δ���ҵ��ú��࣬�޸�ʱ��ʧ��");
	
	return 0;

} 
int change_flight_total(char* x){
		FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n���ҵ��ú��࣬������Ҫ�޸ĵ���Ʊ��");
			char change[20];
			scanf("%s",change);
			strcpy(u->totalTicket,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("δ���ҵ��ú��࣬�޸���Ʊ��ʧ��");
	
	return 0;
} 
int change_flight_sell(char* x){
		FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n���ҵ��ú��࣬������Ҫ�޸ĵ�����Ʊ��");
			char change[20];
			scanf("%s",change);
			strcpy(u->sellTicket,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("δ���ҵ��ú��࣬�޸�����Ʊ��ʧ��");
	
	return 0;
}
int change_flight_user(char* x){
	
		FLIGHT_I* u=flight_i->next;
	
	while(u!=NULL){
		if(strcmp(u->flightNo,x)==0){
			printf("\n���ҵ��ú��࣬������Ҫ�޸ĵĹ�Ʊ�û�");
			char change[20];
			scanf("%s",change);
			strcpy(u->user,change);
			return 1; 
		}
		else{
			printf("\nƥ��%s ʧ��",u->flightNo);
		}
		 u=u->next;
	} 
	
		
		printf("δ���ҵ��ú��࣬�޸Ĺ�Ʊ�û�ʧ��");
	
	return 0;
} 


//�޸Ĺ���Ա����
int change_admin(char* x){
	 change_admin_password(x);
}
int change_admin_password(char* x){
	PASSWORD* u=password->next;
	while(u!=NULL){
		if(strcmp(u->uid,x)==0){
			printf("\n���ҵ����û���������Ҫ�޸ĵ�����");
			char change[20];
			scanf("%s",change);
			strcpy(u->upassword,change);
			return 1;
		}
		else{
			printf("\nƥ��%s ʧ��",u->uid);
		}
		 u=u->next;
	} 
	
		printf("δ���ҵ����û����޸�����ʧ��");
	
	return 0;
	
} 
