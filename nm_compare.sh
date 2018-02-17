./ft_nm $@ > ftnm_result
nm $@ > nm_result
diff ftnm_result nm_result
rm ftnm_result nm_result
