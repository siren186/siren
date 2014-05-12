# LaTeX -*-Makefile-*-
#
# This first section contains macros whose values that you need to
# fill in.
#

AUTOMAKE_OPTIONS	= foreign dist-tarZ no-dependencies

# MAIN_TEX: In order to build your thesis/dissertation, fill in the
# MAIN_TEX macro with the name of your main .tex file -- the one that
# you invoke LaTeX on.

MAIN_TEX	= inilib.tex

# OTHER_SRC_FILES: Put in the names of all the other files that your
# thesis depends on (e.g., other .tex files, figures, etc.) in the
# OTHER_SRC_FILES macro.  This is ensure that whenever one of the
# "other" files changes, "make" will rebuild your paper.  You should
# *not* list any files in this macro that were already listed in
# CHAP_CITE_TEX, above.

OTHER_SRC_FILES	= attribute.tex       interface.tex       registry.tex  \
	      	titlepage.tex		implementation.tex  	intro.tex \
		overview.tex		section.tex \
		op_overload.tex		using.tex	defs.tex ../VERSION

EPS_FIGS	= ndseal_trans.eps

EXTRA_DIST	= $(MAIN_TEX) $(OTHER_SRC_FILES) $(EPS_FIGS)

# If you get a "command not found" for the "dvips" command, uncomment
# one of the two commented out DVIPS macros; the first one is for running
# on Sun (Solaris) machines, the second is for running on IBM RS/6000
# (AIX) machines.

LATEX		= latex
PDFLATEX	= pdflatex
DVIPS		= dvips

#########################################################################
#
# You should not need to edit below this line
#
#########################################################################

SUFFIXES = .tex .dvi .ps .pdf .eps

CHAP_CITE	= $(CHAP_CITE_TEX:.tex=)
MAIN_DVI	= $(MAIN_TEX:.tex=.dvi)
MAIN_PS		= $(MAIN_TEX:.tex=.ps)
MAIN_PDF	= $(MAIN_TEX:.tex=.pdf)
PDF_FIGS	= $(EPS_FIGS:.eps=.pdf)

#
# Some common target names
# Note that the default target is "ps"
#
all: pdf

ps: $(MAIN_PS) 
postscript: ps
pdf: $(MAIN_PDF) 
acrobat: pdf
$(MAIN_PDF): $(PDF_FIGS)

thesis: ps

#
# Make the dependencies so that things build when they need to
#

$(MAIN_PS): $(MAIN_DVI)
$(MAIN_DVI): $(MAIN_TEX) $(CITE_TEX) $(OTHER_SRC_FILES)
$(MAIN_PDF): $(MAIN_TEX) $(CITE_TEX) $(OTHER_SRC_FILES)

#
# General rules
#

.tex.dvi:
	(unset TEXINPUTS; $(LATEX) $*)
	@if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null ); \
	then (unset TEXINPUTS; $(LATEX) $*) ; else :; fi
	@ if ( grep 'Writing index file' $*.log > /dev/null ); \
	then makeindex $* ; (unset TEXINPUTS; $(LATEX) $*) ; fi
	@-if ( grep 'LaTeX Warning: Citation' $*.log > /dev/null ); then \
	  if test "$(CHAP_CITE)" ; then \
	    for file in bogus $(CHAP_CITE) ; do \
	      if test "$$file" != "bogus"; then \
		bibtex $$file ; \
	      fi ; \
	    done ; \
	  else \
	    bibtex $* ; \
	  fi ; \
	  (unset TEXINPUTS; $(LATEX) $*) ; \
	fi
	@if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null || \
	      grep 'LaTeX Warning: Citation' $*.log > /dev/null || \
	      grep 'No file' $*.log > /dev/null); \
	then (unset TEXINPUTS; $(LATEX) $*) ; else :; fi
	@if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null || \
	      grep 'LaTeX Warning: Citation' $*.log > /dev/null); \
	then (unset TEXINPUTS; $(LATEX) $*) ; else :; fi
	@if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null || \
	      grep 'LaTeX Warning: Citation' $*.log > /dev/null); \
	then (unset TEXINPUTS; $(LATEX) $*) ; else :; fi

.dvi.ps:
#	$(DVIPS) -Pps-type1 -o $*.ps $*
	$(DVIPS) -o $*.ps $*

.tex.pdf:
	(unset TEXINPUTS; $(PDFLATEX) $*)
	@if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null ); \
	then (unset TEXINPUTS; $(PDFLATEX) $*) ; else :; fi
	@ if ( grep 'Writing index file' $*.log > /dev/null ); \
	then makeindex $* ; (unset TEXINPUTS; $(PDFLATEX) $*) ; fi
	@-if ( grep 'LaTeX Warning: Citation' $*.log > /dev/null ); then \
	  if test "$(CHAP_CITE)" ; then \
	    for file in bogus $(CHAP_CITE) ; do \
	      if test "$$file" != "bogus"; then \
		bibtex $$file ; \
	      fi ; \
	    done ; \
	  else \
	    bibtex $* ; \
	  fi ; \
	  (unset TEXINPUTS; $(PDFLATEX) $*) ; \
	fi
	@if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null || \
	      grep 'LaTeX Warning: Citation' $*.log > /dev/null || \
	      grep 'No file' $*.log > /dev/null); \
	then (unset TEXINPUTS; $(PDFLATEX) $*) ; else :; fi
	@if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null || \
	      grep 'LaTeX Warning: Citation' $*.log > /dev/null); \
	then (unset TEXINPUTS; $(PDFLATEX) $*) ; else :; fi
	@if ( grep 'LaTeX Warning: Label(s) may' $*.log > /dev/null || \
	      grep 'LaTeX Warning: Citation' $*.log > /dev/null); \
	then (unset TEXINPUTS; $(PDFLATEX) $*) ; else :; fi

.eps.pdf:
	epstopdf $*.eps


#
# Standard targets
#

clean:
	/bin/rm -f *~ *.bak *%

squeaky:
	/bin/rm -f *.log *.aux *.dvi *.blg *.toc *.bbl *.lof *.lot \
		$(MAIN_PS) $(MAIN_DVI) $(MAIN_PDF)
