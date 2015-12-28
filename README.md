# pam-magic-lamp
Small, simple,  sample PAM module with its small test PAM powered service.

## test_pam
```
test_pam [user=<username>] [silent]
```
Will try to start pam and authenticate as <username> or as nobody.
If the silent argument is given test_pam will instruct the PAM not to prompt the user, using the PAM_SILENT flag.

`test_pam` will intialise the PAM transaction as a service called test_pam.
An sample configuration for this service is provided in etc/pam.d/test_pam.

`$ make` will build test_pam to bin/test_pam, this requires libpam and libpam_misc.

`# make install` will install the pam config to /etc/pam.d/

`# make untinstall` will remove the configuration for /etc/pam.d


##pam_lamp 
```
auth	<control>	pam_lamp.so	[debug][use_frist_pass|try_first_pass][lamp=<file>]
```
pam_lamp only provide `pam_sm_authenticate` & and a stub of `pam_set_cred`
This module will honor the PAM_SILENT flag as well a use_first_pass.
If possible module will prompt the use for authentication token with "Who disturbs my slumber ? ".
The authentication token is "aladdin".

This module is not safe for production usage.

`$ make` will build pam_lamp to lib/security/pam_lamp.so 

`# make install` will copy the module to /lib/security/

`# make uninstall`will remove de module from /lib/security/ . It is advised to do so when possible.
