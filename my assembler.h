#include MY_ASSEMBLER_H
#define MY_ASSEMBLER_H

/* 커스텀 헤더 파일 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINES 5000
#define MAX_INST 256
#define MAX_SYMBOL 1000
#define MAX_OPERAND 3

// Instruction을 관리하기 위한 구조체 변수

struct inst_unit{
    char str[10];          //instruction의 이름
    unsigned char op;   //명령어의 OPCODE
    int format;          //instruction의 형식
    int ops;            //instruction의 operand 개수
}
typedef struct inst_unit inst; // Instruction의 정보를 가진 구조체를 관리하는 테이블

// 어셈블리 할 라인 별 소스코드를 토큰 단위로 관리하기 위한 구조체 
struct token_unit {
        char *label;                       //명령어 라인 중 label
        char *operator;                   //명령어 라인 중 operator
        char operand[MAX_OPERAND][20];    //명령어 라인 중 operand
        char comment[100];     //명령어 라인 중 comment
        int locctr;            //효율적 연산을 위해 토큰테이블에 locctr 추가
        char object_code[10];   //토큰단위로 object_code 저장 16진수 (6자리)
};
typedef struct token_unit token ;  // 어셈블리 할 소스코드를 5000라인[MAX_LINE]까지 관리하는 테이블 

// Symbol Table을 관리하기 위한 구조체 
struct symbol_unit {
    char sym[10];          /* 심볼 이름 (label) */
    int addr;               /* 심볼의 주소 (LOC) */
};
typedef struct symbol_unit symbol; // Symbol Table를 관리하기 위한 테이블

// 전역 변수 선언 (extern)
extern token *token_table[MAX_LINES];
extern inst *inst_table[MAX_INST];  // OPTAB으로 사용
extern symbol *symbol_table[MAX_INST]; // SYMTAB으로 사용

extern int line_count; // 총 라인 수
extern int start_addr; // 시작 주소

//inst.data 파일을 읽어 instruction 테이블을 초기화한 다음 입력 소스 파일을 읽어 input_data 배열에 저장하기 위한 함수 코드
int init_inst_table(const char *filename);
int init_input_file(const char *filename);

// SYMTAB/OPTAB 검색/삽입 함수 (새로 추가) [const 함수로 매개변수 추가 및 원본 데이터 훼손 방지]
inst *search_optab(const char *mnemonic);
void add_optab_table(const char *str);
int insert_symtab(const char *label, int addr);
void add_symbol(const char *name, int addr);

// 파일 파싱 함수
void read_and_parse(char *filename);

// Pass 1, Pass 2 추가
int bler_pass_1(void);
int bler_pass_2(void);

// 결과 출력하는 함수
void make_output(const char *filename);

// 메모리를 전부 해제하는 함수
void free_all_memory(void);

#endif
