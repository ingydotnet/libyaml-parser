#include <yaml.h>

#include <stdlib.h>
#include <stdio.h>

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>

int
main(int argc, char *argv[])
{
    int number;

    if (argc < 2) {
        printf("Usage: %s file1.yaml ...\n", argv[0]);
        return 0;
    }

    for (number = 1; number < argc; number ++)
    {
        FILE *file;
        yaml_parser_t parser;
        yaml_event_t event;
        int done = 0;
        int count = 0;
        int error = 0;

        /* printf("[%d] Parsing '%s': ", number, argv[number]); */
        fflush(stdout);

        file = fopen(argv[number], "rb");
        assert(file);

        assert(yaml_parser_initialize(&parser));

        yaml_parser_set_input_file(&parser, file);

        while (!done)
        {
            if (!yaml_parser_parse(&parser, &event)) {
                error = 1;
                break;
            }

            switch (event.type) {
                case YAML_NO_EVENT:
                    printf("YAML_NO_EVENT\n");
                    break;
                case YAML_STREAM_START_EVENT:
                    printf("YAML_STREAM_START_EVENT\n");
                    break;
                case YAML_STREAM_END_EVENT:
                    printf("YAML_STREAM_END_EVENT\n");
                    break;
                case YAML_DOCUMENT_START_EVENT:
                    printf("YAML_DOCUMENT_START_EVENT\n");
                    break;
                case YAML_DOCUMENT_END_EVENT:
                    printf("YAML_DOCUMENT_END_EVENT\n");
                    break;
                case YAML_MAPPING_START_EVENT:
                    printf("YAML_MAPPING_START_EVENT\n");
                    break;
                case YAML_MAPPING_END_EVENT:
                    printf("YAML_MAPPING_END_EVENT\n");
                    break;
                case YAML_SEQUENCE_START_EVENT:
                    printf("YAML_SEQUENCE_START_EVENT\n");
                    break;
                case YAML_SEQUENCE_END_EVENT:
                    printf("YAML_SEQUENCE_END_EVENT\n");
                    break;
                case YAML_SCALAR_EVENT:
                    printf("YAML_SCALAR_EVENT \"%s\"\n", event.data.scalar.value);
                    break;
                case YAML_ALIAS_EVENT:
                    printf("YAML_ALIAS_EVENT\n");
                    break;
                default:
                    break;
            }

            done = (event.type == YAML_STREAM_END_EVENT);

            yaml_event_delete(&event);

            count ++;
        }

        yaml_parser_delete(&parser);

        assert(!fclose(file));

        /* printf("%s (%d events)\n", (error ? "FAILURE" : "SUCCESS"), count); */
    }

    return 0;
}

