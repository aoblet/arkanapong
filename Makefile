all: test
	echo 'ok'

#test pour voir le parcours des fichiers dans les regles d'inférences.

test: src/%.c
	echo $<
