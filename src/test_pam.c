#include <stdio.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>

static const char *err_msg[32] = {"SUCCESS","OPEN_ERR","SYMBOL_ERR","SERVICE_ERR","SYSTEM_ERR","BUF_ERR","PERM_DENIED","AUTH_ERR","CRED_INSUFFICIENT","AUTH_INFO_UNAVAIL","USER_UNKNOWN","MAX_TRIES","NEW_AUTHTOK_REQD","ACCT_EXPIRED","SESSION_ERR","CRED_UNAVAIL","CRED_EXPIRERED","CRED_ERR","NO_MODULE_DATA","CONV_ERR","AUTHTOK_ERR","AUTHTOK_RECOVERY_ERR","AUTHTOK_LOCK_BUSY","AUTHTOK_DISABLE_AGING","TRY_AGAIN","IGNORE","ABORT","AUTHTOK_EXPIERED","MODULE_UNKNOWN","BAD_ITEM","CONV_AGAIN","INCOMPLETE"};

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
		printf("Failed to retreve %s : %s\n", item_msg[item], err_msg[pam_err]);
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
	pam_handle_t *handle = NULL;
	const char *user = "nobody";
	const void *item = NULL;
	
	if(2 <= argc){
		user = argv[1];
	}
	printf("The user is %s\n",user);

	pam_err = pam_start("test_lamp",user,&conv,&handle);
	if(pam_err != PAM_SUCCESS){
		printf("pam_start error : %d %s\n",pam_err,err_msg[pam_err]);
		return pam_err;
	}
	
	pam_err = pam_authenticate(handle,0);
	if(pam_err != PAM_SUCCESS){
		printf("pam_authenticate error :%d %s\n",pam_err,err_msg[pam_err]);
		return pam_err;
	}

	pam_err = pam_acct_mgmt(handle,0);
	if(pam_err != PAM_SUCCESS){
		printf("pam_acct_management error :%d %s\n",pam_err,err_msg[pam_err]);
		return pam_err;
	}

	for(i=1;i<7;i++){
		printf("Now looking up : %s\n",item_msg[i]);
		show_item(i,handle);
	}

	pam_err = pam_end(handle,pam_err);
	return pam_err;
}
