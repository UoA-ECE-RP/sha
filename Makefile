CC=ocamlopt -annot -g
TYPECONV=`ocamlfind query type_conv`
SEXPLIB=`ocamlfind query sexplib`
BATDIR=`ocamlfind query batteries`
LANGUAGELIB=language.cmxa
SRC=language.ml
# Add more examples to this
EXAMPLES=water_tank

all:
	$(CC) -pp "camlp4o -I $(TYPECONV) -I $(SEXPLIB)			\
	pa_type_conv.cma pa_sexp_conv.cma pa_macro.cmo -UDEBUG" -I	\
	$(BATDIR) -I $(SEXPLIB) -c $(SRC)
	$(CC) -a language.cmx -o language.cmxa


test:
	for i in $(EXAMPLES) ; do \
	 	ocamlfind $(CC) -pp "camlp4o pa_macro.cmo -UDEBUG" -I		\
		. -linkpkg -package sexplib,batteries $(LANGUAGELIB) examples/"$$i".ml -o "$$i"; \
	done

clean:
	rm -rf *cm* *o *a *mli *.annot test
	for i in $(EXAMPLES) ; do \
		rm -rf "$$i"; \
	done
