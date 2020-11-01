
int cplr_execute(cplr_t *c) {
  int i;
  int argc = 1 + (c->argc - c->argp);
  char **argv = xcalloc(sizeof(char*), argc+1);
  argv[0] = "c";
  for(i = 1; i < argc; i++) {
    argv[i] = c->argv[c->argp + (i - 1)];
  }
  return tcc_run(c->tcc, argc, argv);
}