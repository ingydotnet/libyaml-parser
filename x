commit df3b7e076512cdb57faeda55edffba12e53fdc83
Author: Tina Müller <cpan2@tinita.de>
Date:   Sun Dec 4 02:54:10 2016 +0100

    Add more escapes and error handling

diff --git a/libyaml-parser.c b/libyaml-parser.c
index cb9df6e..80b701b 100644
--- a/libyaml-parser.c
+++ b/libyaml-parser.c
@@ -20,7 +20,6 @@ int main(int argc, char *argv[]) {
     yaml_event_t event;
     int done = 0;
     int count = 0;
-    int error = 0;
 
     /* printf("[%d] Parsing '%s': ", number, argv[number]); */
     fflush(stdout);
@@ -37,8 +36,8 @@ int main(int argc, char *argv[]) {
 
     while (!done) {
       if (!yaml_parser_parse(&parser, &event)) {
-        error = 1;
-        break;
+        fprintf(stderr, "Error: %s\n", parser.problem);
+        return 1;
       }
 
       switch (event.type) {
@@ -75,7 +74,12 @@ int main(int argc, char *argv[]) {
           printf("-MAP\n");
           break;
         case YAML_SEQUENCE_START_EVENT:
-          printf("+SEQ\n");
+          printf("+SEQ");
+          if (event.data.sequence_start.anchor)
+            printf(" &%s", event.data.sequence_start.anchor);
+          if (event.data.sequence_start.tag)
+            printf(" <%s>", event.data.sequence_start.tag);
+          printf("\n");
           break;
         case YAML_SEQUENCE_END_EVENT:
           printf("-SEQ\n");
@@ -121,8 +125,6 @@ int main(int argc, char *argv[]) {
     }
 
     assert(!fclose(file));
-
-    /* printf("%s (%d events)\n", (error ? "FAILURE" : "SUCCESS"), count); */
   }
 
   return 0;
@@ -141,12 +143,18 @@ void print_escaped(yaml_char_t* str, size_t length) {
       case '\0':
         printf("\\0");
         break;
-      case '\r':
-        printf("\\r");
+      case '\b':
+        printf("\\b");
         break;
       case '\n':
         printf("\\n");
         break;
+      case '\r':
+        printf("\\r");
+        break;
+      case '\t':
+        printf("\\t");
+        break;
       default:
         printf("%c", c);
         break;
