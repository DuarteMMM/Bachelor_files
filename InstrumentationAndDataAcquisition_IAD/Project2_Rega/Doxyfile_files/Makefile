clean:
		rm -rf html
		rm -rf latex

pdf:
		doxygen Doxyfile
		cd latex && $(MAKE) pdf
		cp latex/refman.pdf refman.pdf