//
//  STMPManager.h
//  SMTP

#ifndef STMPManager_h
#define STMPManager_h

typedef struct SMTPClient{
  int socket;
  int buflen;
  char *buf;
}SMTPClient;

struct SMTPClient *createSMTPClient(void);

#endif /* STMPManager_h */
