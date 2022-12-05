#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#define varSize 4
#define R_FRONT 0
#define R_BACK 1
#define AND 0
#define OR 1
int i = 0;
int volatile shell_end = 0;
void shell_end_handler(int){
    shell_end++;
}

typedef struct node {
    void* val;
    struct node * next;
} list;

list* push(list * head, void* val) {
    if(head != NULL){
        list * current = head;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = (list *)malloc(sizeof(list));
        current->next->val = val;
        current->next->next = NULL;
    } else {
       head = (list *)malloc(sizeof(list));
       head->next = NULL;
       head->val = val;
    }
    return head;
}

//-----------------------------
typedef struct simple_command{
    char *command_name;
    char **command_arguments;
} simple_command;

typedef struct conveyor{
    list* simple_command_list;
} conveyor;

typedef struct output_redirect{
    char * out_file_name;
} output_redirect;

typedef struct input_redirect{
    char * in_file_name;
} input_redirect;

typedef struct input_and_output_redirect{
    input_redirect *input;
    output_redirect *output;
} input_and_output_redirect;

typedef struct command{
    input_and_output_redirect *redirect;
    conveyor *conveyor;
} command;

typedef struct conditional_command{
    list* command_list;
    list* conditional_list;
} conditional_command;

typedef struct shell_command{
    list* conditional_command_list;
    list* running_option_list;
} shell_command;

void bracket_handler(char *command_line){
    while(command_line[i]!=')'){
        i++;
    }
    i++;
    printf("%d\n", i);
}

int skip_spaces(char* command_line){
    int j = i;
    while(command_line[i] == ' '){
        i++;
    }
    return i-j;

}
char* in_str(){
    char c;
    int pointer=0;
    char* p = (char *) malloc(varSize);
    do {
        c = getchar();
        if((c == '\n')||(c == EOF)){
            break;
        }
        p[pointer]=c;
        pointer++;
        if(pointer%varSize == 0)
            p = (char *) realloc(p, pointer+varSize);
    } while (1==1);
    p[pointer] = '\0';
    return p;
}

input_redirect* parse_input_redirect(char * command_line){
    input_redirect *cmd;
    cmd = malloc(sizeof(input_redirect));
    cmd->in_file_name = NULL;
    while(command_line[i] == ' ' || command_line[i] == '<'){
        i++;
    }
    int j = i;
    while(command_line[i]!=' '&& command_line[i] != '\0' && command_line[i] != ';' && command_line[i] != '|' && command_line[i] != '&' 
            && command_line[i]!= '<' && command_line[i] != '>'){
        i++;
    }
    int size = sizeof(char)*(i-j);
    cmd ->in_file_name= malloc(size+1);
    strncpy(cmd->in_file_name, command_line + j,size);
    skip_spaces(command_line);
    printf("input: %s\n", cmd->in_file_name);
    return cmd;
    
}
output_redirect* parse_output_redirect(char * command_line){
    output_redirect *cmd;
    cmd = malloc(sizeof(output_redirect));
    cmd->out_file_name = NULL;
    while(command_line[i] == ' ' || command_line[i] == '>'){
        i++;
    }
    int j = i;
    while(command_line[i]!=' '&& command_line[i] != '\0' && command_line[i] != ';' && command_line[i] != '|' && command_line[i] != '&' 
            && command_line[i]!= '<' && command_line[i] != '>'){
        i++;
    }
    int size = sizeof(char)*(i-j);
    cmd ->out_file_name = malloc(size+1);
    strncpy(cmd->out_file_name, command_line + j,size);
    skip_spaces(command_line);
    printf("output: %s\n", cmd->out_file_name);
    return cmd;
}
simple_command* parse_simple_command(char * command_line){
    simple_command *cmd;
    cmd = malloc(sizeof(simple_command));
    cmd->command_arguments = NULL;
    cmd->command_name = NULL;
    skip_spaces(command_line);
    int j = i;
    while(command_line[i]!=' '&& command_line[i] != '\0' && command_line[i] != ';' && command_line[i] != '|' && command_line[i] != '&' 
            && command_line[i]!= '<' && command_line[i] != '>'){
        i++;
    }
    int size = sizeof(char)*(i-j);
    cmd -> command_name = malloc(size+1);
    strncpy(cmd->command_name, command_line + j, size);
    i = j;
    printf("scmd name: %s\n", cmd->command_name);
    int p = 0, cont = 1;
    cmd->command_arguments = malloc(sizeof(char*));
    while(cont){
        skip_spaces(command_line);
        j = i;
        while(command_line[i]!=' '&& command_line[i] != '\0' && command_line[i] != ';' && command_line[i] != '|' && command_line[i] != '&' 
            && command_line[i]!= '<' && command_line[i] != '>'){
            i++;
        }
        if(command_line[i] != ' '){
            cont = 0;
        }
        if(i == j){
            break;
        }
        size = (i-j)*sizeof(char);
        cmd->command_arguments[p] = malloc(size+1);
        strncpy(cmd->command_arguments[p], command_line+j, size);
        cmd->command_arguments[p][size] = '\0';
        p++;
        printf("scmd args: %d %s\n", p, cmd->command_arguments[p-1]);
        cmd->command_arguments = realloc(cmd->command_arguments, (p+1)*sizeof(char*));
    }
    skip_spaces(command_line);
    return cmd;
}

//! CORRECT WORK

conveyor* parse_conveyor(char * command_line){
    conveyor *cmd;
    cmd = malloc(sizeof(conveyor));
    cmd->simple_command_list = NULL;
    while(command_line[i] != '\0' && command_line[i] != ';' && (command_line[i] != '|' || command_line[i+1] != '|') && command_line[i] != '&' 
            && command_line[i]!= '<' && command_line[i] != '>'){
        cmd->simple_command_list = push(cmd->simple_command_list, parse_simple_command(command_line));
        if(command_line[i] == '|' && command_line[i] != '\0' && command_line[i+1] != '|'){
            i++;
        }
    }
    return cmd;
}

// вроде так
input_and_output_redirect* parse_input_and_output_redirect(char * command_line){
    input_and_output_redirect* io;
    io = malloc(sizeof(input_and_output_redirect));
    io->input = NULL;
    io->output = NULL;
    int j = skip_spaces(command_line);
    if(command_line[i]=='<'){ // {<перенаправление ввода >} <перенаправление вывода>
        i = i-j;
        io->input = parse_input_redirect(command_line);
        j = skip_spaces(command_line);
        if(command_line[i] == '>'){
            i = i-j;
            io->output = parse_output_redirect(command_line);
        }
    } else { // {<перенаправление вывода>} <перенаправление ввода>
        i = i-j;
        io->output = parse_output_redirect(command_line);
        j = skip_spaces(command_line);
        if(command_line[i] == '<'){
            i = i-j;
            io->input = parse_input_redirect(command_line);
        }
    }
    return io;
}

//! MOST DANGEROUS(JOKE)
command* parse_command(char *command_line){

    int j = skip_spaces(command_line);
    command *cmd;
    cmd = malloc(sizeof(command));
    if(command_line[i] == '('){  // случай (<Команда Shellа>)
        bracket_handler(command_line);
        skip_spaces(command_line);
    }
    else if(command_line[i] == '<' || command_line[i] == '>'){ // случай <перенаправление ввода/вывода> <Конвейер>
        i = i - j;
        cmd->redirect = parse_input_and_output_redirect(command_line);
        cmd->conveyor = parse_conveyor(command_line);
    }
    else { // случай <Конвейер> {<перенаправление ввода/вывода>}(не факт)
        i = i - j;
        cmd->conveyor = parse_conveyor(command_line);
        int j = skip_spaces(command_line);
        int g = i;
        if(command_line[i] == '<' || command_line[i] == '>'){ // случай <Конвейер> <перенаправление ввода/вывода>(не факт)
            i = i - j;
            cmd->redirect = parse_input_and_output_redirect(command_line);
        }
    }
    return cmd;
}
/*
 * Checked
 */
conditional_command* parse_conditional_command(char *command_line){
    conditional_command *cmd;
    cmd = malloc(sizeof(conditional_command));
    cmd ->command_list = NULL;
    cmd ->conditional_list = NULL;
    int *condition;
    while(command_line[i] != '\0' && command_line[i] != ';' && (command_line[i] != '&' || command_line[i+1] =='&')){
        cmd->command_list = push(cmd->command_list, parse_command(command_line));
        condition = malloc(sizeof(int));
        if(command_line[i] == '&' && command_line[i+1] == '&'){
            condition[0] = AND;
            cmd->conditional_list = push(cmd->conditional_list, condition);
            i+=2;
        }
        else if(command_line[i] == '|' && command_line[i+1] == '|'){
            
            condition[0] = OR;
            cmd->conditional_list = push(cmd->conditional_list, condition);
            i+=2;
        }
    }
    return cmd;
}
/*
 * Checked 
 */
shell_command* parse_shell_command(char * command_line){ //  все пробелы скипаются
    shell_command* cmd;
    cmd = malloc(sizeof(shell_command));
    cmd -> conditional_command_list = NULL;
    cmd -> running_option_list = NULL;
    int *option;
    i = 0;
    while(command_line[i] != '\0'){
        cmd->conditional_command_list = push(cmd->conditional_command_list , parse_conditional_command(command_line));
        option = malloc(sizeof(int));
        if(command_line[i] == ';'){
            option[0] = R_FRONT;
            cmd->running_option_list = push(cmd->running_option_list, option);
        }
        else if(command_line[i] == '&'){
            option[0] = R_BACK;
            cmd->running_option_list = push(cmd->running_option_list, option);
        }
        else if(command_line[i] == '\0'){
            break;
        }
        i++;
    }
    return cmd;
}

//*-----------------
//* Processing Part
//*-----------------

void process_output_redirect(output_redirect * cmd){ //  все пробелы скипаются   

}
void process_input_redirect(input_redirect * cmd){ //  все пробелы скипаются   

}
void process_simple_command(simple_command * cmd){

}
void process_input_and_output_redirect(input_and_output_redirect * cmd){

}

void process_conveyor(conveyor * cmd){ 

}

void process_command(command* cmd){

}
void turn_background_regime(conditional_command *cmd){
    printf("background_regime %d\n", ((int*)cmd->conditional_list->val)[0]);
}

//TODO Background regime

void process_conditional_command(conditional_command * cmd){
    printf("front_regime %d\n", ((int*)cmd->conditional_list->val)[0]);
}

// *Checked

void process_shell_command(shell_command * cmd){
    list *p = cmd->conditional_command_list;
    list *bp = cmd->running_option_list;
    while(p != NULL){
        if(bp != NULL){
            if(((int*) bp->val)[0] == R_FRONT){
                process_conditional_command(p->val);
            } else {
                turn_background_regime(p->val);
            }
            bp = bp->next;
        } else {
            process_conditional_command(p->val);
        }
        p = p->next;
    }
}

int main(int argc, char **argv)
{
    signal(SIGTSTP, shell_end_handler);
    char *command_line;
    shell_command *cmd;
    while(shell_end == 0){
        command_line = in_str();
        cmd = parse_shell_command(command_line);
        process_shell_command(cmd);
    }
}