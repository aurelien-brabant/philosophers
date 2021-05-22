all:
	make -C philo_one

clean:
	make clean -C philo_one
	make clean -C lib

fclean:
	make fclean -C philo_one
	make fclean -C lib

re: fclean all
