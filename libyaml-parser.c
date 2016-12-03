#include <yaml.h>

#include <stdlib.h>
#include <stdio.h>

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>

void print_escaped(yaml_char_t* str, size_t length);

int main(int argc, char *argv[]) {
  int max = (argc < 2 ? 2 : argc);
  int number;

  for (number = 1; number < max; number++) {
    FILE *file;
    yaml_parser_t parser;
    yaml_event_t event;
    int done = 0;
    int count = 0;
    int error = 0;

    /* printf("[%d] Parsing '%s': ", number, argv[number]); */
    fflush(stdout);

    if (argc < 2)
      file = fopen("/dev/stdin", "rb");
    else
      file = fopen(argv[number], "rb");
    assert(file);

    assert(yaml_parser_initialize(&parser));

    yaml_parser_set_input_file(&parser, file);

    while (!done) {
      if (!yaml_parser_parse(&parser, &event)) {
        error = 1;
        break;
      }

      switch (event.type) {
        case YAML_NO_EVENT:
          printf("???\n");
          break;
        case YAML_STREAM_START_EVENT:
          printf("+STR\n");
          break;
        case YAML_STREAM_END_EVENT:
          printf("-STR\n");
          break;
        case YAML_DOCUMENT_START_EVENT:
          printf("+DOC");
          if (!event.data.document_start.implicit)
            printf(" ---");
          printf("\n");
          break;
        case YAML_DOCUMENT_END_EVENT:
          printf("-DOC");
          if (!event.data.document_end.implicit)
            printf(" ...");
          printf("\n");
          break;
        case YAML_MAPPING_START_EVENT:
          printf("+MAP");
          if (event.data.mapping_start.anchor)
            printf(" &%s", event.data.mapping_start.anchor);
          if (event.data.mapping_start.tag)
            printf(" <%s>", event.data.mapping_start.tag);
          printf("\n");
          break;
        case YAML_MAPPING_END_EVENT:
          printf("-MAP\n");
          break;
        case YAML_SEQUENCE_START_EVENT:
          printf("+SEQ\n");
          break;
        case YAML_SEQUENCE_END_EVENT:
          printf("-SEQ\n");
          break;
        case YAML_SCALAR_EVENT:
          printf("=VAL");
          if (event.data.scalar.anchor)
            printf(" &%s", event.data.scalar.anchor);
          if (event.data.scalar.tag)
            printf(" <%s>", event.data.scalar.tag);
          switch (event.data.scalar.style) {
            case YAML_PLAIN_SCALAR_STYLE:
              printf(" :");
              break;
            case YAML_SINGLE_QUOTED_SCALAR_STYLE:
              printf(" '");
              break;
            case YAML_DOUBLE_QUOTED_SCALAR_STYLE:
              printf(" \"");
              break;
            case YAML_LITERAL_SCALAR_STYLE:
              printf(" |");
              break;
            case YAML_FOLDED_SCALAR_STYLE:
              printf(" >");
              break;
          }
          print_escaped(event.data.scalar.value, event.data.scalar.length);
          printf("\n");
          break;
        case YAML_ALIAS_EVENT:
      	  printf("=ALI *%s\n", event.data.alias.anchor);
          break;
        default:
          break;
      }

      done = (event.type == YAML_STREAM_END_EVENT);

      yaml_event_delete(&event);

      count ++;
    }

    assert(!fclose(file));

    /* printf("%s (%d events)\n", (error ? "FAILURE" : "SUCCESS"), count); */
  }

  return 0;
}

void print_escaped(yaml_char_t* str, size_t length) {
  int number;
  char c;

  for (number = 0; number < length; number++) {
    c = *(str++);
    switch(c) {
      case '\\':
        printf("\\\\");
        break;
      case '\0':
        printf("\\0");
        break;
      case '\r':
        printf("\\r");
        break;
      case '\n':
        printf("\\n");
        break;
      default:
        printf("%c", c);
        break;
    }
  }
}
