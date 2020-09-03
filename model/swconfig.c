/** @file SWCONFIG.C 
		  Configure StreamWork
	Interpret YAML file

	https://www.redhat.com/sysadmin/yaml-tips
*/

#include <stdio.h>
#include <yaml.h>
//#include <assert.h>
#include "sw.h"

struct cfg_ cfg;

/*
    	printf("Node [%d]: %d\n", i++, node->type);
    if(node->type == YAML_SCALAR_NODE) {
      printf("Scalar [%d]: %s\n", node->data.scalar.style, node->data.scalar.value);
*/
static void SetConf( yaml_node_t *node) {
	static int i=1;

	printf("Node [%d]: %d\n", i++, node->type);
    
	if(node->type == YAML_SCALAR_NODE) {
	     // printf("Scalar [%d]: %s\n", node->data.scalar.style, node->data.scalar.value);
	}
}

int ConfigError(char *fname)
{
  FILE *file;
  yaml_parser_t parser;
  yaml_document_t document;
  yaml_node_t *node;
  int i = 1;

  file = fopen(fname, "rb");
  if(!file) {
	FAIL1(Missing Config file);
  }

  if(!yaml_parser_initialize(&parser)) {
	FAIL1(Configuration parse failure);
  }

  yaml_parser_set_input_file(&parser, file);

  if (yaml_parser_load(&parser, &document)) {
	node = yaml_document_get_node(&document, i);
	while(node) {
    		SetConf(node);
    		node = yaml_document_get_node(&document, i++);
  	}
  }

  yaml_document_delete(&document);
  yaml_parser_delete(&parser);
  fclose(file);

  return 0;
}


/*    End of SWCONFIG.C  */
