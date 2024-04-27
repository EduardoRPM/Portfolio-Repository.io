#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nombre[30];
  int tipo;
  int tam;
  long dir, ptr_atr, sig_ent;
} TEntidad;

typedef struct {
  char nombre[30];
  int tipo, tam;
  int clave;
  long dir, ptr_sig_atr, sig_ent;
} TAtributo;

typedef struct nodoE {
  TEntidad e;
  struct nodoE *sig;
  struct nodA *aba;
} TNodoE;

typedef struct nodA {
  TAtributo a;
  struct nodA *sig;
} TNodoA;

typedef struct {
  void *bloque;
  int tam;
  int desp;
} TBloque;

TEntidad captura_entidad();
void crea_dicc(char nom_arch[]);
void alta_entidad(char nom_ach[], TEntidad e);
void imprime_entidad(TEntidad e);
void imprime_diccionario(char nom_arch[]);
TAtributo captura_atributo();
void imprime_atributo(TAtributo a);
void inserta_atributo(char nom_dic[], char nom_ent[], TAtributo a);
void elimina_atr(char nom_dic[], char nom_entidad[], char nom_atr[]);
void baja_entidad(char nom_ach[], char nom_entidad[]);
void modifica_entidad(char nom_ach[], char nom_entidad[], char nuevo_nombre[]);
void modifica_atributo(char nom_ach[], char nom_entidad[], char nom_atributo[],
                       char nuevo_nombre[], int nuevo_tipo, int nueva_long);

void menu();
TNodoE *busca_entidad(TNodoE *c, char nom_ent[]);
TBloque crea_bloque(TNodoE *e);
void captura_bloque(TNodoE *e, TBloque b);
int compara_bloque(TNodoE *e, TBloque b1, TBloque b2);
void captura_bloque(TNodoE *e, TBloque b);
TNodoE *carga_diccionario(char nom_arch[]);
TNodoE *crea_nodoE(TEntidad e);
TNodoA *crea_nodoA(TAtributo a);
void alta_SecuencialReg(TBloque b, TNodoE *e);
void imprime_bloque(TNodoE *e, TBloque b1); // c
void muestra_tabla(TNodoE *e);
void imprime_DicLis(TNodoE *c);
void elimina_bloque(int clave_p, TNodoE *e);

int main(void) {
  menu();
  return 0;
}

void menu() {
  int opcion = 0;
  int submenu_opcion = 0;
  char nom_arch[30];
  TEntidad e;
  TAtributo a;
  char nom_ent[30], nom_atr[30];
  char nuevo_nombre[30];
  int nuevo_tipo;
  int nueva_long;
  TNodoE *nodoE = NULL;
  TBloque b, b1;
  TNodoE *cab = carga_diccionario(nom_arch);
  int clave_p;
  printf("Ingrese el nombre del archivo del diccionario: ");
  scanf("%s", nom_arch);

  do {
    printf("\nMenu:\n");
    printf("1. Crear diccionario\n");
    printf("2. Abrir diccionario\n");
    printf("3. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      crea_dicc(nom_arch);
      break;
    case 2:
      do {
        printf("\nSubmenu:\n");
        printf("1. Alta de Entidad\n");
        printf("2. Baja de Entidad\n");
        printf("3. Modificacion de Entidad\n");
        printf("4. Alta de Atributo\n");
        printf("5. Baja de Atributo\n");
        printf("6. Modificacion de Atributo\n");
        printf("7. Muestra de Diccionario\n");
        printf("8. Alta bloque\n");
        printf("9. Baja bloque\n");
        printf("10. Muestra bloque\n");
        printf("11. Salir del submenu\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &submenu_opcion);

        switch (submenu_opcion) {
        case 1:
          e = captura_entidad();
          alta_entidad(nom_arch, e);
          break;
        case 2:
          printf("Nombre de la entidad a eliminar: ");
          scanf("%s", nom_ent);
          baja_entidad(nom_arch, nom_ent);
          break;
        case 3:
          printf("Nombre de la entidad a modificar: ");
          scanf("%s", nom_ent);
          printf("Nuevo nombre de la entidad: ");
          scanf("%s", nuevo_nombre);
          modifica_entidad(nom_arch, nom_ent, nuevo_nombre);
          break;

        case 4:
          a = captura_atributo();
          printf("Nombre de la entidad a la que se agregará el atributo: ");
          scanf("%s", nom_ent);
          inserta_atributo(nom_arch, nom_ent, a);
          break;
        case 5:
          printf("Nombre de la entidad de la que se eliminará el atributo: ");
          scanf("%s", nom_ent);
          printf("Nombre del atributo a eliminar: ");
          scanf("%s", nom_atr);
          elimina_atr(nom_arch, nom_ent, nom_atr);
          break;
        case 6:
          printf("Nombre de la entidad que contiene el atributo: ");
          scanf("%s", nom_ent);
          printf("Nombre del atributo a modificar: ");
          scanf("%s", nom_atr);
          printf("Nuevo nombre del atributo: ");
          scanf("%s", nuevo_nombre);
          printf("Nuevo tipo del atributo (0: Entero, 1: Flotante, 2: "
                 "Caracter, 3: Cadena): ");
          scanf("%d", &nuevo_tipo);
          printf("Nueva longitud del atributo: ");
          scanf("%d", &nueva_long);
          modifica_atributo(nom_arch, nom_ent, nom_atr, nuevo_nombre,
                            nuevo_tipo, nueva_long);
          break;

        case 7:
          imprime_diccionario(nom_arch);
          break;
        case 8:
          if (!cab)
            cab = carga_diccionario(nom_arch);
          printf("nombre de la entidad que queremos capturar: ");
          scanf("\n%[^\n]", nom_ent);
          nodoE = busca_entidad(cab, nom_ent);
          b = crea_bloque(nodoE);
          captura_bloque(nodoE, b);
          alta_SecuencialReg(b, nodoE);
          break;
        case 9:
          if (!cab)
            cab = carga_diccionario(nom_arch);
          printf("nombre de la entidad que queremos eliminar: ");
          scanf("\n%[^\n]", nom_ent);
          nodoE = busca_entidad(cab, nom_ent);
          printf("clave primaria del bloque: ");
          scanf("%d", &clave_p);
          elimina_bloque(clave_p, nodoE);
          break;
        case 10:
          cab = carga_diccionario(nom_arch);
          printf("nombre de la entidad que queremos imprimir: ");
          scanf("\n%[^\n]", nom_ent);
          nodoE = busca_entidad(cab, nom_ent);
          muestra_tabla(nodoE);
          break;
        case 11:
          printf("Saliendo del submenu...\n");
          break;
        default:
          printf("Opcion invalida. Por favor, intente de nuevo.\n");
          break;
        }
      } while (submenu_opcion != 11);
      break;
    case 3:
      printf("Saliendo...\n");
      break;
    default:
      printf("Opción inválida. Por favor, intente de nuevo.\n");
      break;
    }
  } while (opcion != 3);

  // imprime_DicLis(cab);
  // printf("nombre de la entidad que queremos capturar: ");
  // scanf("\n%[^\n]", nom_ent);
  // nodoE = busca_entidad(cab, nom_ent);
  // printf("crea\n");
  // b = crea_bloque(nodoE);
  // printf("captura\n");
  // captura_bloque(nodoE, b);
  // printf("imprime\n");
  // imprime_bloque(nodoE,b);
  // printf("alta\n");
  // alta_SecuencialReg(b,nodoE);
  // muestra_tabla(nodoE);
  // imprime_diccionario(nom_arch);
}

TEntidad captura_entidad() {
  TEntidad e;

  printf("Nombre:");
  scanf("\n%[^\n],", e.nombre);
  e.dir = e.ptr_atr = e.sig_ent = -1L;
  return e;
}
void imprime_entidad(TEntidad e) {
  printf("Nombre: %s\n", e.nombre);
  printf("Dir:%ld\n", e.dir);
  printf("Sig Ent:%ld\n", e.sig_ent);
  printf("Ptr  Atrib:%ld\n", e.ptr_atr);
}
void crea_dicc(char nom_arch[]) {
  long cab = -1L;
  FILE *f;

  f = fopen(nom_arch, "wb");
  if (f) {
    fwrite(&cab, sizeof(long), 1, f);
    fclose(f);
  } else
    printf("No se pudo crear el diccionario\n");
}
void alta_entidad(char nom_ach[], TEntidad e) {
  FILE *f;
  long cab;
  TEntidad aux, ant;

  f = fopen(nom_ach, "rb+");
  if (!f) {
    printf("No se pudo abrir el diccionario");
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  fseek(f, 0, SEEK_END); // Mover al fin del archivo
  e.dir = ftell(f);
  if (cab == -1) {
    cab = e.dir;
    fseek(f, 0, SEEK_SET);            // Mover al inicio del archivo
    fwrite(&cab, sizeof(long), 1, f); // Actualiza cabecera en el archivo.
  } else {
    fseek(f, cab, SEEK_SET);
    fread(&aux, sizeof(TEntidad), 1, f);
    if (strcmp(aux.nombre, e.nombre) > 0) {
      e.sig_ent = cab;
      cab = e.dir;
      fseek(f, 0, SEEK_SET);            // Mover al inicio del archivo
      fwrite(&cab, sizeof(long), 1, f); // Actualiza la cabecera en el archivo
    } else {
      while (strcmp(aux.nombre, e.nombre) < 0 && aux.sig_ent != -1) {
        ant = aux;
        fseek(f, aux.sig_ent, SEEK_SET);
        fread(&aux, sizeof(TEntidad), 1, f);
      }
      if (strcmp(aux.nombre, e.nombre) > 0) {
        e.sig_ent = aux.dir;
        ant.sig_ent = e.dir;
        fseek(f, ant.dir, SEEK_SET);
        fwrite(&ant, sizeof(TEntidad), 1, f);
      } else {
        aux.sig_ent = e.dir;
        fseek(f, aux.dir, SEEK_SET);
        fwrite(&aux, sizeof(TEntidad), 1, f);
      }
    }
  }
  fseek(f, e.dir, SEEK_SET);
  fwrite(&e, sizeof(TEntidad), 1, f);

  fclose(f);
}
void imprime_diccionario(char nom_arch[]) {
  FILE *f;
  long cab;
  TEntidad aux;
  TAtributo aux_a;
  long pos;

  f = fopen(nom_arch, "rb");
  if (f == NULL) {
    printf("No se pudo abrir el archivo\n");
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  if (cab != -1) {
    while (cab != -1) {
      fseek(f, cab, SEEK_SET);
      fread(&aux, sizeof(TEntidad), 1, f);
      imprime_entidad(aux);
      pos = aux.ptr_atr;
      while (pos != -1) {
        fseek(f, pos, SEEK_SET);
        fread(&aux_a, sizeof(TAtributo), 1, f);
        imprime_atributo(aux_a);
        // printf("pos-----------%ld\n",pos);
        pos = aux_a.ptr_sig_atr;
      }

      cab = aux.sig_ent;
    }
  } else {
    printf("El diccionario esta vacio\n");
  }
  fclose(f);
}

void baja_entidad(char nom_ach[], char nom_entidad[]) {
  FILE *f;
  long cab;
  TEntidad ant, aux;

  f = fopen(nom_ach, "rb+");
  if (!f) {
    printf("No se pudo abrir el diccionario");
    return;
  }

  fread(&cab, sizeof(long), 1, f);

  fseek(f, cab, SEEK_SET);
  fread(&ant, sizeof(TEntidad), 1, f);
  fread(&aux, sizeof(TEntidad), 1, f);

  while (strcmp(aux.nombre, nom_entidad) != 0 && aux.sig_ent != -1) {
    ant = aux;
    fseek(f, aux.sig_ent, SEEK_SET);
    fread(&aux, sizeof(TEntidad), 1, f);
  }
  if (strcmp(aux.nombre, nom_entidad) == 0) {
    if (ant.dir == aux.dir) { // es el primero
      cab = aux.sig_ent;
      fseek(f, 0, SEEK_SET);
      fwrite(&cab, sizeof(long), 1, f); // Actualizar la cabecera en el archivo
    } else {                            // si se encuentra y no es el primero
      ant.sig_ent = aux.sig_ent;
      fseek(f, ant.dir, SEEK_SET);
      fwrite(&ant, sizeof(TEntidad), 1,
             f); // Actualizar la entidad anterior en el archivo
    }
  } else {
    printf("no existe ");
  }
  fclose(f);
}

TAtributo captura_atributo() {
  TAtributo a;

  printf("Nombre de atributo:");
  scanf("\n%[^\n],", a.nombre);
  printf("Tipo (1:int, 2:char, 3:cadena, 4:float):");
  scanf("%d", &a.tipo);
  switch (a.tipo) {
  case 1:
    a.tam = sizeof(int);
    break;
  case 2:
    a.tam = sizeof(char);
    break;
  case 3:
    printf("cadena: ");
    scanf("%d", &a.tam);
    break;
  case 4:
    a.tam = sizeof(float);
    break;
  }
  printf("Clave (1: Primaria, 2: Externa, 3: No clave):");
  scanf("%d", &a.clave);

  a.dir = a.ptr_sig_atr = a.sig_ent = -1L;
  return a;
}

void imprime_atributo(TAtributo a) {
  printf("Nombre de atributo: %s\n", a.nombre);
  printf("Tipo: %d\n", a.tipo);
  printf("Tamaño: %d\n", a.tam);
  printf("Clave: %d\n", a.clave);
  printf("Dir: %ld\n", a.dir);
  printf("Prt Sig Atr: %ld\n", a.ptr_sig_atr);
  printf("Sig Ent: %ld\n", a.sig_ent);
}

void inserta_atributo(char nom_dic[], char nom_ent[], TAtributo a) {
  FILE *f;
  long cab;
  TEntidad e;
  TAtributo aux_a;
  int enc = 0;

  f = fopen(nom_dic, "rb+");
  if (f == NULL) {
    printf("no se pudo abrir "); // corregir el mensaje
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  while (cab != -1 && !enc) {
    fseek(f, cab, SEEK_SET);
    fread(&e, sizeof(TEntidad), 1, f);
    if (strcmp(e.nombre, nom_ent) == 0) {
      enc = 1;
    } else {
      cab = e.sig_ent;
      enc = 0;
    }
  } // busqueda de entidades
  if (enc) {
    // buscar el final del atributo
    fseek((f), 0, SEEK_END);
    a.dir = ftell(f);
    // conectar
    if (e.ptr_atr == -1L) {
      e.ptr_atr = a.dir;
      // escribir actualizar la entidad
      fseek(f, e.dir, SEEK_SET);
      fwrite(&e, sizeof(TEntidad), 1, f);
    }
    fseek(f, a.dir, SEEK_SET);
    fwrite(&a, sizeof(TAtributo), 1, f);
  } else { // Si no se encontró la entidad, no deberíamos hacer nada
    printf("Entidad no encontrada.\n");
    fclose(f);
    return;
  }
  cab = e.ptr_atr;
  while (cab != -1L) {
    fseek(f, cab, SEEK_SET);
    fread(&aux_a, sizeof(TAtributo), 1, f);

    if (aux_a.ptr_sig_atr == -1L) {
      aux_a.ptr_sig_atr = a.dir;
      fseek(f, cab, SEEK_SET);
      fwrite(&aux_a, sizeof(TAtributo), 1, f);
      break;
    }
    cab = aux_a.ptr_sig_atr;
  }
  // si cab == -1L, significa que no se encontró ningún atributo en la entidad
  if (cab == -1L) {
    e.ptr_atr = a.dir;
    fseek(f, e.dir, SEEK_SET);
    fwrite(&e, sizeof(TEntidad), 1, f);
  }
  fseek(f, a.dir, SEEK_SET);
  fwrite(&a, sizeof(TAtributo), 1, f);

  fclose(f);
}

void elimina_atr(char nom_dic[], char nom_entidad[], char nom_atr[]) {
  TEntidad e;
  TAtributo aux, ant;
  long cab, pos; // pos aux
  FILE *f;
  int enc = 0;

  f = fopen(nom_dic, "rb+");
  if (!f) {
    printf("no existe el dicc ");
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  while (cab != -1 && !enc) { // Agregar la condición !enc para detener la
                              // búsqueda cuando se encuentra la entidad
    fseek(f, cab, SEEK_SET);
    fread(&e, sizeof(TEntidad), 1, f);
    if (strcmp(e.nombre, nom_entidad) == 0) {
      enc = 1;
    } else {
      cab = e.sig_ent;
    }
  }
  if (enc == 1) {
    pos = e.ptr_atr;
    enc = 0;
    while (pos != -1 && !enc) {
      fseek(f, pos, SEEK_SET);
      fread(&aux, sizeof(TAtributo), 1, f);
      if (strcmp(aux.nombre, nom_atr) == 0) {
        enc = 1;
      } else {
        ant = aux;
        pos = aux.ptr_sig_atr;
      }
    }
    if (enc) {
      if (pos == e.ptr_atr) {
        e.ptr_atr = aux.ptr_sig_atr;
        fseek(f, e.dir, SEEK_SET);
        fwrite(&e, sizeof(TEntidad), 1, f);
      } else {
        ant.ptr_sig_atr = aux.ptr_sig_atr;
        fseek(f, ant.dir, SEEK_SET);
        fwrite(&ant, sizeof(TAtributo), 1, f);
      }
    } else {
      printf("atributo no encontrada");
    }
  } else {
    printf("entidad no encontrada");
  }
  fclose(f); // Asegurarse de cerrar el archivo antes de salir de la función
}

void modifica_entidad(char nom_ach[], char nom_entidad[], char nuevo_nombre[]) {
  FILE *f;
  long cab;
  TEntidad aux;

  f = fopen(nom_ach, "rb+");
  if (!f) {
    printf("No se pudo abrir el diccionario");
    return;
  }

  fread(&cab, sizeof(long), 1, f);

  int entidad_encontrada = 0;

  while (cab != -1 && !entidad_encontrada) {
    fseek(f, cab, SEEK_SET);
    fread(&aux, sizeof(TEntidad), 1, f);
    if (strcmp(aux.nombre, nom_entidad) == 0) {
      entidad_encontrada = 1;
    } else {
      cab = aux.sig_ent;
    }
  }

  if (entidad_encontrada) {
    strcpy(aux.nombre, nuevo_nombre);
    fseek(f, aux.dir, SEEK_SET);
    fwrite(&aux, sizeof(TEntidad), 1, f);
    printf("Entidad modificada con éxito.\n");
  } else {
    printf("Entidad no encontrada.\n");
  }

  fclose(f);
}

void modifica_atributo(char nom_ach[], char nom_entidad[], char nom_atributo[],
                       char nuevo_nombre[], int nuevo_tipo, int nueva_long) {
  FILE *f;
  long cab;
  TEntidad aux_ent;
  TAtributo aux_atr;

  f = fopen(nom_ach, "rb+");
  if (!f) {
    printf("No se pudo abrir el diccionario");
    return;
  }

  fread(&cab, sizeof(long), 1, f);

  int entidad_encontrada = 0;
  int atributo_encontrado = 0;

  while (cab != -1 && !entidad_encontrada) {
    fseek(f, cab, SEEK_SET);
    fread(&aux_ent, sizeof(TEntidad), 1, f);
    if (strcmp(aux_ent.nombre, nom_entidad) == 0) {
      entidad_encontrada = 1;
    } else {
      cab = aux_ent.sig_ent;
    }
  }

  if (entidad_encontrada) {
    long dir_atr = aux_ent.ptr_atr;

    while (dir_atr != -1 && !atributo_encontrado) {
      fseek(f, dir_atr, SEEK_SET);
      fread(&aux_atr, sizeof(TAtributo), 1, f);
      if (strcmp(aux_atr.nombre, nom_atributo) == 0) {
        atributo_encontrado = 1;
      } else {
        dir_atr = aux_atr.ptr_sig_atr;
      }
    }

    if (atributo_encontrado) {
      strcpy(aux_atr.nombre, nuevo_nombre);
      aux_atr.tipo = nuevo_tipo;
      aux_atr.tam = nueva_long;
      fseek(f, aux_atr.dir, SEEK_SET);
      fwrite(&aux_atr, sizeof(TAtributo), 1, f);
      printf("Atributo modificado con éxito.\n");
    } else {
      printf("Atributo no encontrado.\n");
    }
  } else {
    printf("Entidad no encontrada.\n");
  }

  fclose(f);
}

TBloque crea_bloque(TNodoE *e) {
  TNodoA *a;
  TBloque b;
  b.desp = 0;
  b.tam = 0;
  a = e->aba;
  while (a != NULL) {
    if (a->a.clave == 1)
      b.desp = b.tam;
    b.tam += a->a.tam;
    a = a->sig;
  }
  b.tam += sizeof(long) * 2;
  b.bloque = malloc(b.tam);
  *((long *)(b.bloque + (b.tam - (sizeof(long) * 2)))) = -1L;
  *((long *)(b.bloque + (b.tam - sizeof(long)))) = -1L;
  return (b);
}

void captura_bloque(TNodoE *e, TBloque b) {
  TNodoA *a;
  int d = 0;

  printf("%s:\n", e->e.nombre);
  a = e->aba;
  while (a != NULL) {
    printf("%s:", a->a.nombre);
    //(1. Int 2. Char 3.Cadena 4 float)
    switch (a->a.tipo) {
    case 1:
      scanf("\n%d", (int *)(b.bloque + d));
      break;
    case 2:
      scanf("\n%c", (char *)(b.bloque + d));
      break;
    case 3:
      scanf("\n%[^\n]", (char *)(b.bloque + d));
      break;
    case 4:
      scanf("\n%f", (float *)(b.bloque + d));
      break;
    }
    d += a->a.tam;
    a = a->sig;
  }
}

void imprime_bloque(TNodoE *e, TBloque b) {
  TNodoA *a;
  int d = 0;
  printf("%s:\n", e->e.nombre);
  a = e->aba;
  while (a != NULL) {
    printf("%s:", a->a.nombre);
    //(1. Int 2. Char 3.Cadena 4 float)
    switch (a->a.tipo) {
    case 1:
      printf("%d\n", *((int *)(b.bloque + d)));
      break;
    case 2:
      printf("%c\n", *((char *)(b.bloque + d)));
      break;
    case 3:
      printf("%s\n", (char *)(b.bloque + d));
      break;
    case 4:
      printf("%f\n", *((float *)(b.bloque + d)));
      break;
    }
    d += a->a.tam;
    a = a->sig;
  }
}

int compara_bloque(TNodoE *e, TBloque b1, TBloque b2) {
  TNodoA *a;
  int b = 0;

  a = e->aba;
  while (a->a.clave != 1)
    a = a->sig;
  switch (a->a.tipo) //(1. Int 2. Char 3.Cadena 4 float)
  {
  case 1:
    if (*((int *)(b1.bloque + b1.desp)) < *((int *)(b2.bloque + b2.desp)))
      b = -1;
    else if (*((int *)(b1.bloque + b1.desp)) > *((int *)(b2.bloque + b2.desp)))
      b = 1;
    else
      b = 0;
    break;
  case 2:
    if (*((char *)(b1.bloque + b1.desp)) < *((char *)(b2.bloque + b2.desp)))
      b = -1;
    else if (*((char *)(b1.bloque + b1.desp)) >
             *((char *)(b2.bloque + b2.desp)))
      b = 1;
    else
      b = 0;
    break;
  case 3:
    b = strcmp((char *)(b1.bloque + b1.desp), (char *)(b2.bloque + b2.desp));
    break;
  case 4:
    if (*((float *)(b1.bloque + b1.desp)) < *((float *)(b2.bloque + b2.desp)))
      b = -1;
    else if (*((float *)(b1.bloque + b1.desp)) >
             *((float *)(b2.bloque + b2.desp)))
      b = 1;
    else
      b = 0;
    break;
  }
  return b;
}

TNodoE *carga_diccionario(char nom_arch[]) {
  FILE *f;
  long cab;
  TEntidad aux;
  TAtributo aux_a;
  long pos;
  TNodoE *c = NULL, *auxE;
  TNodoA *auxA;

  f = fopen(nom_arch, "rb");
  if (f == NULL) {
    printf("No se pudo abrir el archivo\n");
    return c;
  }
  fread(&cab, sizeof(long), 1, f);
  if (cab != -1) {
    while (cab != -1) {
      fseek(f, cab, SEEK_SET);
      fread(&aux, sizeof(TEntidad), 1, f);
      if (c == NULL) {
        c = crea_nodoE(aux);
        auxE = c;
      } else {
        auxE->sig = crea_nodoE(aux);
        auxE = auxE->sig;
      }
      // imprime_entidad(aux);
      pos = aux.ptr_atr;
      while (pos != -1L) {
        fseek(f, pos, SEEK_SET);
        fread(&aux_a, sizeof(TAtributo), 1, f);
        if (auxE->aba == NULL) {
          auxE->aba = crea_nodoA(aux_a);
          auxA = auxE->aba;
        } else {
          auxA->sig = crea_nodoA(aux_a);
          auxA = auxA->sig;
        }
        // imprime_atributo(aux_a);
        pos = aux_a.ptr_sig_atr;
      }
      cab = aux.sig_ent;
    }

  } else {
    return c;
  }
  fclose(f);
  return c;
}
TNodoE *crea_nodoE(TEntidad e) {
  TNodoE *n_e;
  n_e = (TNodoE *)malloc(sizeof(TNodoE));
  if (n_e) {
    n_e->e = e;
    n_e->aba = NULL;
    n_e->sig = NULL;
  }
  return (n_e);
}
TNodoA *crea_nodoA(TAtributo a) {
  TNodoA *n_a;
  n_a = (TNodoA *)malloc(sizeof(TNodoA));
  if (n_a) {
    n_a->a = a;
    n_a->sig = NULL;
  }
  return (n_a);
}
void imprime_DicLis(TNodoE *c) {
  TNodoA *correA;
  TNodoE *correE;

  correE = c;
  while (correE) {
    imprime_entidad(correE->e);
    correA = correE->aba;
    while (correA) {
      imprime_atributo(correA->a);
      correA = correA->sig;
    }
    correE = correE->sig;
  }
}

TNodoE *busca_entidad(TNodoE *c, char nom_ent[]) {
  TNodoE *corre = c;
  int enc = 0;
  while (corre && !enc) {
    if (strcmp(nom_ent, corre->e.nombre) == 0)
      enc = 1;
    else
      corre = corre->sig;
  }
  return corre;
}
void alta_SecuencialReg(TBloque b, TNodoE *e) {
  FILE *f;
  char nom_arch[50];
  long cab, dir;
  TBloque b1, b2;
  int band;

  strcpy(nom_arch, e->e.nombre);
  strcat(nom_arch, ".dat");

  f = fopen(nom_arch, "rb+");
  if (f == NULL) {
    f = fopen(nom_arch, "wb+");
    cab = -1L;
    fwrite(&cab, sizeof(long), 1, f);
    fseek(f, 0, SEEK_SET);
  }
  fread(&cab, sizeof(long), 1, f);
  if (cab == -1) // El archivo no tiene bloques
  {
    fseek(f, 0, SEEK_END);
    cab = ftell(f);
    *((long *)(b.bloque + b.tam - (sizeof(long) * 2))) = cab;
    fseek(f, 0, SEEK_SET);
    fwrite(&cab, sizeof(long), 1, f);
    fseek(f, cab, SEEK_SET);
    fwrite(b.bloque, b.tam, 1, f);
  } else {
    fseek(f, 0, SEEK_END);
    dir = ftell(f);
    *((long *)(b.bloque + b.tam - (sizeof(long) * 2))) = dir;
    b1 = crea_bloque(e);
    fseek(f, cab, SEEK_SET);
    fread(b1.bloque, b1.tam, 1, f);
    band = compara_bloque(e, b, b1);
    if (band < 0) {
      *((long *)(b.bloque + b.tam - (sizeof(long)))) = cab;
      cab = dir;
      fseek(f, 0, SEEK_SET);
      fwrite(&cab, sizeof(long), 1, f);
      fseek(f, cab, SEEK_SET);
      fwrite(b.bloque, b.tam, 1, f);
    } else {
      b2 = b1;
      dir = *((long *)(b2.bloque + b2.tam - (sizeof(long))));
      while (dir != -1L && band > 0) {
        fseek(f, dir, SEEK_SET);
        b1 = crea_bloque(e);
        fread(b1.bloque, b1.tam, 1, f);
        band = compara_bloque(e, b, b1);
        if (band > 0) {
          dir = *((long *)(b1.bloque + b1.tam - (sizeof(long))));
          free(b2.bloque);
          b2 = b1;
        }
      }

      *((long *)(b.bloque + b.tam - (sizeof(long)))) =
          *((long *)(b2.bloque + b2.tam - (sizeof(long))));
      *((long *)(b2.bloque + b2.tam - (sizeof(long)))) =
          *((long *)(b.bloque + b.tam - (sizeof(long) * 2)));
      dir = *((long *)(b2.bloque + b2.tam - (sizeof(long) * 2)));
      fseek(f, dir, SEEK_SET);
      fread(b2.bloque, b2.tam, 1, f);
      dir = *((long *)(b.bloque + b.tam - (sizeof(long) * 2)));
      fseek(f, dir, SEEK_SET);
      fread(b.bloque, b.tam, 1, f);
    }
  }
  fclose(f);
}

void muestra_tabla(TNodoE *e) {
  FILE *f;
  char nom_arch[50];
  long cab, dir;
  TBloque b1;
  int band;

  strcpy(nom_arch, e->e.nombre);
  strcat(nom_arch, ".dat");
  printf("nombre del archivo: %s\n", nom_arch);
  f = fopen(nom_arch, "rb+");
  if (f == NULL) {
    printf("Esa tabla no existe\n");
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  b1 = crea_bloque(e);
  while (cab != -1L) {
    fseek(f, cab, SEEK_SET);
    fread(b1.bloque, b1.tam, 1, f);
    imprime_bloque(e, b1);
    cab = *((long *)(b1.bloque + b1.tam - (sizeof(long))));
  }
  fclose(f);
}

void elimina_bloque(int clave_p, TNodoE *e) {
  FILE *f;
  char nom_arch[50];
  long cab, dir, ante_dir = -1;
  TBloque b1;

  strcpy(nom_arch, e->e.nombre);
  strcat(nom_arch, ".dat");

  f = fopen(nom_arch, "rb+");
  if (f == NULL) {
    printf("El archivo no existe\n");
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  if (cab == -1) // El archivo no tiene bloques
  {
    printf("El archivo esta vacio\n");
    return;
  }

  while (cab != -1) {
    fseek(f, cab, SEEK_SET);
    b1 = crea_bloque(e);
    fread(b1.bloque, b1.tam, 1, f);

    if (*((int *)(b1.bloque + b1.desp)) == clave_p) {
      if (ante_dir == -1) // primero
      {
        cab = *((long *)(b1.bloque + b1.tam - sizeof(long))); //-1L
        fseek(f, 0, SEEK_SET);
        fwrite(&cab, sizeof(long), 1, f);
      } else {
        TBloque b2;
        long corre_dir = *((long *)(b1.bloque + b1.tam - sizeof(long)));
        fseek(f, ante_dir, SEEK_SET);
        b2 = crea_bloque(e);
        fread(b2.bloque, b2.tam, 1, f);
        *((long *)(b2.bloque + b2.tam - sizeof(long))) = corre_dir;
        fseek(f, ante_dir, SEEK_SET);
        fwrite(b2.bloque, b2.tam, 1, f);
        free(b2.bloque);
      }

      free(b1.bloque);
      break;
    }

    ante_dir = cab;
    cab = *((long *)(b1.bloque + b1.tam - sizeof(long)));
    free(b1.bloque);
  }

  fclose(f);
}
