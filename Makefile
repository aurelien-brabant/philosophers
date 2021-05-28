all:
	make --no-print-directory -C philo_one

clean:
	@make clean --no-print-directory -C philo_one
	@make clean --no-print-directory -C lib

fclean:
	@make fclean --no-print-directory -C philo_one
	@make fclean --no-print-directory -C lib

re: fclean all
