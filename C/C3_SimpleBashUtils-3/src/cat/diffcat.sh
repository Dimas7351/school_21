filename=Makefile;
echo ----------------------------------------------*CAT 1
diff <(cat -b test_files/test_1_cat.txt) <(./s21_cat -b test_files/test_1_cat.txt) -s
echo ----------------------------------------------*CAT 2
diff <(cat -e "test_files/test_2_cat.txt") <(./s21_cat -e "test_files/test_2_cat.txt") -s
echo ----------------------------------------------*CAT 3
diff <(cat -n "test_files/test_3_cat.txt") <(./s21_cat -n "test_files/test_3_cat.txt") -s
echo ----------------------------------------------*CAT 5
diff <(cat -s "test_files/test_5_cat.txt") <(./s21_cat -s "test_files/test_5_cat.txt") -s
echo ----------------------------------------------*CAT 6
diff <(cat -t "test_files/test_4_cat.txt") <(./s21_cat -t "test_files/test_4_cat.txt") -s



echo ----------------------------------------------*CAT 7
diff <(cat -b diffcat.sh) <(./s21_cat -b diffcat.sh) -s
echo ----------------------------------------------*CAT 8
diff <(cat -e diffcat.sh) <(./s21_cat -e diffcat.sh) -s
echo ----------------------------------------------*CAT 9
diff <(cat -n diffcat.sh) <(./s21_cat -n diffcat.sh) -s
echo ----------------------------------------------*CAT 10
diff <(cat -s diffcat.sh) <(./s21_cat -s diffcat.sh) -s
echo ----------------------------------------------*CAT 11
diff <(cat -t diffcat.sh) <(./s21_cat -t diffcat.sh) -s
echo ----------------------------------------------*CAT 12
diff <(cat diffcat.sh) <(./s21_cat diffcat.sh) -s

