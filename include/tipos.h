#ifndef __TIPOS_H__
#define __TIPOS_H__ // DECLARAÇÕES ANTECIPADAS (isso informa ao compilador que essas estruturas existem, mas ele não precisa saber como elas são definidas AGORA)



// declaração antecipada das structs
typedef struct Jogador Jogador;
typedef struct Plataforma Plataforma;
typedef struct Pergunta Pergunta;



//as enums não precisam de declaração antecipada

typedef enum {
    NORMAL,        // plataforma segura
    PERGUNTA,      // plataforma que ativa a pergunta de lógica
    QUEBRAVEL,     // plataforma que some após o uso
    PROP_LOGICA    // plataforma que ativa uma proposição (P ou Q)
} TipoPlataforma;


#endif // __TIPOS_H__
