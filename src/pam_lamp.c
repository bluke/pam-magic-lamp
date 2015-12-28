#define PAM_SM_AUTH

#include <syslog.h>
#include <string.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>
 

struct opt {
	const char *debug;
	const char *use_first_pass;
	const char *try_first_pass;
	const char *lamp;	
};

static const char *get_option(const char *option,int argc,const char **argv){
	int i;
	size_t len;

	if(option==NULL||argc==0||argv==NULL)
		return NULL;

	len = strlen(option);

	for(i=0; i<argc; i++){
		if(strncmp(argv[i],option,len)==0){
			if(argv[i][len]== '=')
				return &(argv[i][len+1]);
			else
				return "\0";
		}
	}
	return NULL;
}

static const struct opt *parse_options(struct opt *res,int argc,const char **argv){
	
	res->debug = get_option("debug",argc,argv);
	res->use_first_pass = get_option("use_first_pass",argc,argv);
	res->try_first_pass = get_option("try_first_pass",argc,argv);
	res->lamp = get_option("lamp",argc,argv);
	
	return res;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv){
	int pam_err=-1;
	char *token=NULL;
	struct opt *opts,options;
	opts=&options;
	parse_options(opts,argc,argv);

	if(opts->debug!=NULL){
		pam_syslog(pamh,LOG_NOTICE,"SM_AUTH started with flags debug:%d use_first_pass:%d try_first_pass:%d lamp:%d ",opts->debug!=NULL,opts->use_first_pass!=NULL,opts->try_first_pass!=NULL,opts->lamp!=NULL);
		if(opts->lamp!=NULL)
			pam_syslog(pamh,LOG_DEBUG,"SM_AUTH started with lamp %s",opts->lamp);
	}
	
	if(opts->use_first_pass!=NULL||opts->try_first_pass!=NULL){
		pam_err = pam_get_item(pamh,PAM_AUTHTOK,(const void**)&token);
		if(pam_err==PAM_SUCCESS)
			if(strcmp(token,"aladdin")==0){
				return PAM_SUCCESS;
			}
			else{
				pam_err=PAM_AUTH_ERR;
			}	
	}
	if(!((opts->use_first_pass!=NULL)||(flags&PAM_SILENT))){

		pam_err=pam_prompt(pamh,PAM_PROMPT_ECHO_OFF,&token,"Who disturbs my slumber ? ");
		if(pam_err == PAM_SUCCESS){
			if(strcmp(token,"aladdin")==0){
				return PAM_SUCCESS;
			}
			else{
				pam_err=PAM_AUTH_ERR;
			}
		free(token);
		}
	}
	
	return pam_err;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv){

	return PAM_CRED_ERR;
}
