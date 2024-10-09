//
// Created by lyk12 on 24-9-19.
//

#ifndef COMMAND_H
#define COMMAND_H

typedef void (*CommandHandler)(int argc, char* argv[]);

typedef struct Command {
    char *name;
    CommandHandler handler;
}command;

void execute_command(int argc, char **argv);

void Init(int argc, char **argv);

void Hash_object(int argc,char **argv);

void Cat_file(int argc,char **argv);

void Commit(int argc,char **argv);

void Log(int argc,char **argv);

void Checkout(int argc,char **argv);

void Ls_tree(int argc,char **argv);

void Branch(int argc,char **argv);

void Tag(int argc,char **argv);

void Show_ref(int argc,char **argv);

void Add(int argc,char **argv);

void Rm(int argc,char **argv);

void Ls_files(int argc,char **argv);

void Status(int argc,char **argv);

void Check_ignore(int argc,char **argv);

#endif //COMMAND_H
