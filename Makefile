CC=ocamlopt -annot -g
TYPECONV=`ocamlfind query type_conv`
SEXPLIB=`ocamlfind query sexplib`
BATDIR=`ocamlfind query batteries`
SRC=language.ml

all:
	$(CC) -pp "camlp4o -I $(TYPECONV) -I $(SEXPLIB)			\
	pa_type_conv.cma pa_sexp_conv.cma pa_macro.cmo -UDEBUG" -I	\
	$(BATDIR) -I $(SEXPLIB) -I ../error -c $(SRC)

clean:
	rm -rf *cm* *o *a *mli *.annot
