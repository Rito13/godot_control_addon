#! /usr/bin/bash
. ./python\ md\ doc\ generator/.venv/bin/activate
python3 ./python\ md\ doc\ generator/make_md.py doc_classes/ python\ md\ doc\ generator/GDEngine_doc/ -o markdown_doc/
