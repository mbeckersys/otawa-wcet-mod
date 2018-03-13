type token =
  | ID of (string)
  | BIN_CONST of (Int32.t * int)
  | BIN_CONST_64 of (Int64.t * int)
  | CARD_CONST of (Int32.t)
  | CARD_CONST_64 of (Int64.t)
  | FIXED_CONST of (float)
  | STRING_CONST of (string)
  | DOLLAR
  | ACTION
  | ALIAS
  | ATTR
  | BOOL
  | CANON
  | CARD
  | CASE
  | COERCE
  | DEFAULT
  | DO
  | ELSE
  | ENDDO
  | ENDIF
  | ENUM
  | ERROR
  | EXTEND
  | FIX
  | FLOAT
  | FOR
  | FORMAT
  | IF
  | IN
  | IMAGE
  | INITIALA
  | INT
  | LET of (int)
  | MEM of (int)
  | MODE of (int)
  | OP of (int)
  | REG of (int)
  | SWITCH
  | SYNTAX
  | THEN
  | TYPE of (int)
  | VAR of (int)
  | VOLATILE
  | PORTS
  | RESOURCE of (int)
  | USES
  | EXCEPTION of (int)
  | MACRO
  | EOF
  | NOT
  | OR
  | AND
  | LEQ
  | GEQ
  | EQU
  | NEQ
  | LEFT_SHIFT
  | RIGHT_SHIFT
  | DOUBLE_STAR
  | ROTATE_RIGHT
  | ROTATE_LEFT
  | DOUBLE_COLON
  | DOUBLE_DOT
  | BIT_LEFT
  | BIT_RIGHT
  | EQ
  | EXCLAM
  | PIPE
  | CIRC
  | AMPERS
  | GT
  | LT
  | SHARP
  | PLUS
  | MINUS
  | STAR
  | SLASH
  | PERCENT
  | TILD
  | COLON
  | COMMA
  | LBRACE
  | RBRACE
  | LBRACK
  | RBRACK
  | LPAREN
  | RPAREN
  | SEMI
  | DOT
  | AROBAS

val top :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> unit
