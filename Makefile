all:
	make --no-print-directory -C philo_one
	make --no-print-directory -C philo_two
	make --no-print-directory -C philo_three

clean:
	@make clean --no-print-directory -C philo_one
	@make clean --no-print-directory -C philo_two
	@make clean --no-print-directory -C philo_three
	@make clean --no-print-directory -C lib

fclean:
	@make fclean --no-print-directory -C philo_one
	@make fclean --no-print-directory -C philo_two
	@make fclean --no-print-directory -C philo_three
	@make fclean --no-print-directory -C lib

re: fclean all
