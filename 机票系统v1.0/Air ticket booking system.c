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
	char user_sex[5];//�Ա�
	char user_phonenumber[15];//��ϵ�绰
	char user_chinaid[20];//���֤
	char user_bookinginformation[100];//Ԥ���ĺ�����Ϣ
	char user_password[20];//����
}USER_I;

typedef struct flight_information{
   char flightNo[15];   //�����
   char start[10];      //��ʼվ
   char end[10];       //�յ�վ
   char day[20];          //����ʱ��
   char  totalTicket[10];     //Ԥ��Ʊ����
   char  sellTicket[10];      //����Ʊ����
   char user[FLIGHTMAX][20];//��Ʊ�û��˺�
}FLIGHT_I;  //����ṹ��

typedef struct Administrator_information{
	int admin_id;//����Ա�˺�
	char admin_password[20];//����
} ADMIN_I;

/*�������ܺ���


*/
int select(int x);//ѡ����� 
int select_user();//�û���ѡ�����
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
int type; 
char *UID;
int main(){
	char user_id[20];
	//UID=login(user_id);//ʵ��ʹ�������¼������ʱ��ע�͵����� 
	UID="20181101051";//����ʱ�����ֱ�Ӵ����¼ 
	type=judje(UID);//����Ա��1����ͨ�û���0 
	show(type);
	showflight();
	//printf("TYPE==%d\n",type);
	select(type);
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
				printf("�û�%sΪ����Ա\n",userid);
				return 1;

		}
	}

	printf("�û�%sΪ��ͨ�û�\n",userid);
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
				printf("��¼�ɹ�",userid);
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
		scanf("%d",&select);
		switch(select){
			case 0:	
					printf("���沢�˳�%d\n",select);
					exit(0);
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
		scanf("%d",&select);
		switch(select){
			case 0:	
					printf("���沢�˳�%d\n",select);
					exit(0);
					break;
			case 3:searchme(UID); 
					break;
			default:
					show(type);
					printf("\0����������������");
		}
	
		
	}
	   
}



int adduser(){//�����û� (����ԱȨ��)
	
}



