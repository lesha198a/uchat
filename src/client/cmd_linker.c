#include "../../inc/client.h"

int signed_in = 0;
bool inputReady = false;
char* author = NULL;
char *text = NULL;
bool joined = false;
char *chan = NULL;

const char *db_getfield(char *line, int num) {
    if (line == NULL)
        return NULL;
    const char *tok;
    for (tok = strtok(line, ";");
         tok && *tok;
         tok = strtok(NULL, ";")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

void sendSimpleMSG(char *text) {
    setInput(text);
}

void sendSignIn(char *login, char *password) {
    if (signed_in==1) return;
    signed_in = 0;
    char tosend[512];
    setNick(login);
    snprintf(tosend,511,"/signin %s;%s;\r\n",login,password);
    setInput(tosend);
}

void sendSignUp(char *login, char *password) {
    if (signed_in==1) return;
    signed_in = 0;
    setNick(login);
    char tosend[512];
    snprintf(tosend,511,"/signup %s;%s;\r\n",login,password);
    setInput(tosend);

}

void respondHandler(char *decryptedText, t_user *user) {
    char *tmp = strdup(decryptedText);
    char *first_buf = strdup(db_getfield(tmp, 1));
    free(tmp);
    tmp = NULL;
    tmp = strdup(decryptedText);
    char *second_buf = strdup(db_getfield(tmp, 2));
    free(tmp);
    tmp = NULL;
    tmp = strdup(decryptedText);
    char *third_buf = strdup(db_getfield(tmp, 3));
    free(tmp);
    tmp = NULL;
    if (strcmp(first_buf, SERVER_code) == 0) {
        if (strcmp(second_buf, STATUS_code) == 0) {
            if (strcmp(third_buf,SIGN_GOOD)==0) {
                signed_in=1;
                user->loggedin=true;
            } else if (strcmp(third_buf,SIGN_BAD)==0) {
                signed_in=2;
            }
        } else if (strcmp(second_buf, ERROR_code) == 0 && signed_in == 1) {

        } else if (strcmp(second_buf, REPLY_code) == 0 && signed_in == 1) {
            author=strdup("server");
            text=strdup(third_buf);
        }
    } else if (strcmp(first_buf, USER_code) == 0 && signed_in == 1) {
        if (strcmp(second_buf, REPLY_code) == 0) {
            tmp = strdup(decryptedText);
            //printf("%s", tmp);
            char *tmp_ = (char*) db_getfield(tmp, 4);
            char *text1;
            if (tmp_!=NULL)
                text1 = strdup(tmp_);
            else
                text1 = strdup("");
            free(tmp);
            author=strdup(third_buf);
            text=strdup(text1);
            free(text1);
        }
    }
    free(first_buf);
    free(second_buf);
    free(third_buf);
}

void sendJoinAndLeavePrev(char *toChat) {
    if (joined) {
        sendLeave(chan);
        free(chan);
    }
    char tosend[512];
    snprintf(tosend,511,"/join %s\r\n",toChat);
    setInput(tosend);
    chan=strdup(toChat);
    joined=true;
}

void sendLeave(char *Chat) {
    char tosend[512];
    snprintf(tosend,511,"/leave %s\r\n",Chat);
    setInput(tosend);
}

int checkSignSTT() {
    return signed_in;
}

bool isInputReady () {
    return inputReady;
}

void setInputReady(bool value) {
    inputReady = value;
}

int msgReceive (char **author1, char **text1) {
    if (author!=NULL && text != NULL) {
        *author1 = strdup(author);
        *text1 = strdup(text);
        free(author);
        free(text);
        author = NULL;
        text = NULL;
        return 1;
    }
    return 0;
}
