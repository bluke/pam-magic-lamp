#include <stdio.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>


static const char *item_msg[14] = {"","SERVICE","USER","TTY","RHOST","CONV","AUTHTOK","OLDAUTHTOK","RUSER","USER_PROMPT","FAIL_DELAY","XDISPLAY","XAUTHDATA","AUTHTOK_TYPE"};

static struct pam_conv conv = {
	misc_conv,
	NULL
	};

void show_item(int item,pam_handle_t *handle){
	int pam_err;
	const void *object;

	pam_err = pam_get_item(handle,item,&object);
	if(pam_err!=PAM_SUCCESS){
		printf("Failed to retreve %s : %s\n", item_msg[item], pam_strerror(handle,pam_err));
	}
	else{
		if(object!=NULL){
			printf("%s is : %s\n", item_msg[item], (char*)object);
		}
		else{
			printf("%s is NULL\n",item_msg[item]);
		}
	}	
}

int main(int argc,char *argv[]){

	int pam_err,i;
	int pam_flag = 0;
	pam_handle_t *handle = NULL;
	const char *user = "nobody";
	const void *item = NULL;
	
	for (i=1;i<argc;i++)
	{
		if(strncmp(argv[i],"user=",5)==0)
			user = &(argv[i][5]);
		if(strncmp(argv[i],"silent",6)==0)
			pam_flag = PAM_SILENT;
	}

	printf("The user is %s\n",user);

	pam_err = pam_start("test_lamp",user,&conv,&handle);
	if(pam_err != PAM_SUCCESS){
		printf("pam_start error : %d %s\n",pam_err,pam_strerror(handle,pam_err));
		return pam_err;
	}
	
	pam_err = pam_authenticate(handle,pam_flag);
	if(pam_err != PAM_SUCCESS){
		printf("pam_authenticate error :%d %s\n",pam_err,pam_strerror(handle,pam_err));
		return pam_err;
	}
	else{
		printf("Authentication succesful !!\n");
	}


	/*pam_err = pam_acct_mgmt(handle,0);
	if(pam_err != PAM_SUCCESS){
		printf("pam_acct_management error :%d %s\n",pam_err,pam_strerror(handle,pam_err));
		return pam_err;
	
	
	for(i=1;i<7;i++){
		printf("Now looking up : %s\n",item_msg[i]);
		show_item(i,handle);
	}
	*/
	pam_err = pam_end(handle,pam_err);
	return pam_err;
}
