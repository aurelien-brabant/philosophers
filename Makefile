all:
	make --no-print-directory -C philo_one
	make --no-print-directory -C philo_two

clean:
	@make clean --no-print-directory -C philo_one
	@make clean --no-print-directory -C philo_two
	@make clean --no-print-directory -C lib

fclean:
	@make fclean --no-print-directory -C philo_one
	@make fclean --no-print-directory -C philo_two
	@make fclean --no-print-directory -C lib

re: fclean all
