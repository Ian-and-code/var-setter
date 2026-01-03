# que es varsetter?

varsetter es un interprete chico para definir variables y funciones desde texto (txt)
y despues poder usarlas desde c++

sirve como mini lenguaje / dsl simple
no es un parser completo ni un lenguaje grande

# como se usa?

## syntaxis

todas las lineas siguen esta forma:

nombre: tipo = valor;

terminan siempre en ;

---

## variables

ejemplos:

x: double = 10 + 5;
msg: str = "hola";
flag: bool = true;

tipos soportados:
- double
- str
- bool

las expresiones de double son simples
solo soporta:
a + b
a - b
a * b
a / b

no hay precedencia ni expresiones largas

---

## funciones

definicion:

myfunc: function = (a,b,c){ a + b + c };

reglas importantes:
- sin espacios entre args (a,b,c) y NO (a, b, c)
- todos los args son double
- siempre devuelve double
- el cuerpo solo soporta expresiones simples (a + b)

uso:

result: double = myfunc(1,2,3);
sin espacios entre args

---

## uso desde c++

Env env;
Env* envp = &env;

interpret_text(envp, file_content);

---

## getters

gets disponibles:
- getDouble -> double
- getStr -> std::string
- getBool -> bool
- getFunc -> Function

uso:

double x = getDouble(envp, "x");
std::string s = getStr(envp, "msg");
bool b = getBool(envp, "flag");

---

## usar funciones desde c++

Function f = getFunc(envp, "myfunc");
double r = f({1, 2, 3});

---

## limitaciones (importante)

- el lenguaje es sensible a espacios
- no usar espacios en listas de argumentos
- no hay lexer ni ast
- el parsing es directo con strings
- es un interprete simple, pensado para ser chico

esto es intencional, no es un bug oculto
