LATEXCMD = pdflatex -shell-escape
export max_print_line = 1048576

.PHONY: help
help:
	@echo "This makefile builds KACTL (KTH ACM Contest Template Library)"
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast	- to build the PDF, quickly (only runs LaTeX once)"
	@echo "	make UPC	- to build the PDF"
	@echo "	make test	- to run the fuzzy tests"
	@echo "	make clean	- to clean up the build process"
	@echo "	make veryclean	- to clean up and remove kactl.pdf"
	@echo "	make help	- to show this information"
	@echo ""
	@echo "For more information see the file 'doc/README'"

.PHONY: fast
fast:
	cd build && $(LATEXCMD) UPC.tex </dev/null
	cp build/UPC.pdf UPC.pdf

.PHONY: UPC
UPC: test-session.pdf
	cd build && $(LATEXCMD) UPC.tex && $(LATEXCMD) UPC.tex
	cp build/UPC.pdf UPC.pdf

.PHONY: test
test:
	python2 fuzz-tests/fuzz.py

.PHONY: clean
clean:
	cd build && rm -f kactl.aux kactl.log kactl.tmp kactl.toc UPC.pdf kactl.ptc

.PHONY: veryclean
veryclean: clean
	rm -f UPC.pdf test-session.pdf

test-session.pdf: content/test-session/chapter.tex
	cd build && $(LATEXCMD) test-session.tex
	cp build/test-session.pdf test-session.pdf
