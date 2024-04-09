## Задания по курсу "Параллельное программирование", МФТИ ФРКТ, 2024

Данный репозиторий содержит проекты, представленные в качестве лабораторных работ по курсу паралельного программирования. Подробное описание каждой задачи содержится в соотвествующих директориях репозитория. 

### MPI
Для решения задач используется **MPI ( Message Passing Interface )**. MPI это стандартизованный механизм для построения параллельных программ в модели обмена сообщениями. Стандарт разрабатывается объединением MPI Forum.

MPI предоставляет следующие возможности: 
- Обеспечение удобной абстракции над протоколами сетевого взаимодействия
- Логическая организация кластера, а именно организация виртуальной топологичсекой сети поверх физических протоколов
- Функции синхронизации и коммуникации для параллельных операций
- Кроссплатформенная реализация стандарта
- Биндинги в разные языки программирования
- Ориентированность на слабосвязанный MIMD, однако MPI пригоден для сильносвязанного MIM при организации многопроцессности
- Новые версии стандарта поддерживают гибридные архитектуры с общей памятью

MPI содержит в своем составе mpd - сервисный процесс, выполняющийся на узлах и обеспечивающий поддержек виртуальной топологии. Может быть сконфигурирован под конкретную задачу. Также в MPI входит утилита mpirun, которая является менеджером запуска, обеспечивающий корректный старт программ и распределение их экземпляров по вычислительным узлам. Запуск на локальной машине не требует дополнительных настроек mpirun и mpd.

Перед запуском проектов для сборки необходимо установить toolchain **MPI**. 

### Проекты
1. [Численное решение уравнения переноса с помощью технологии **MPI**.](https://github.com/RustamSubkhankulov/parprog/tree/main/transfer_equation)
2. [Ускорение подсчёта числа $\pi$ с помощью технологии **MPI**.](https://github.com/RustamSubkhankulov/parprog/tree/main/pi_estimation)
3. [Измерение задержки передачи сообщений между двумя узлами сети с помощью технологии **MPI**.](https://github.com/RustamSubkhankulov/parprog/tree/main/comm_delay)
4. [Базовый пример использования **MPI**.](https://github.com/RustamSubkhankulov/parprog/tree/main/basic)
