#!/bin/bash

Rscript --vanilla speedup_logscale.R 2 1 experiment1_exectime.txt exp1k0xbrute.pdf

Rscript --vanilla speedup_logscale.R 3 1 experiment1_exectime.txt exp1k-1xbrute.pdf

Rscript --vanilla speedup_logscale.R 3 2 experiment1_exectime.txt exp1k-1xk0.pdf


