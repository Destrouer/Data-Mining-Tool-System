# Data Mining Tool System
Проект **Data Mining Tool System** - Инструментальная система интеллектуального анализа данных (ИСИАД) представляет собой программный проект, позволяющий пользователю использовать интеллектуальные методы анализа данных для решения поставленных задач.

 Проект выполняется студентами ННГУ им. Лобачевского в рамках выпускной работы
## Описание струкруры репозитория

Данный репозиторий содержит исходный код и другие документы проекта ИСИАД. Они сгруппированы в следующих папках:

- **bin** - содержит бинарные файлы стабильной версии проекта и библиотек, используемых в нем.
- **project-files** - содержит исходный код проекта и текущую версию базы данных.
- **reports** - выпускные работы и презентации к ним
- **tech-doc** - техническая документация проекта: диаграммы классов, описание API, UML-диаграммы и т.п.
- **working-doc** - рабочая документация проекта: требования к реализации определенной функциональности, документирование интеграционных процессов и т.д.

###Структура папок
####bin
Данная папка содержит:

- **DMTS** - скомпилированные в сборке Release файлы последней стабильной версии проекта.
- **SQLite** - необходимые для компиляции проекта dll, обеспечивающие работу с SQLite. При сборке новой версии проекта предварительно необходимо:
	1. Положить в папку, где будет собираться проект, dll из директории *lib-debug* или *lib-release* в зависимости от того, какая сборка будет осуществляться.
	2. Туда же положить dll-файл из директории x64 или x86 в зависимости от того, под какую архитектуру будет собираться решение.

####project-files
Программный код проекта написан на языке **C#** и представляет собой **solution**, созданный в среде **Microsoft Visual Studio 2013**. В нем содержатся следующие проекты:

- **MainProjectDMTS** - проект, связующий все остальные проекты системы. Содержит главную форму, которая позволяет запустить любой другой из перечисленных ниже проектов.
- **Desision Trees** - библиотека + формы работы с *деревьями решений*
- **NeuroWnd** - библиотека + формы работы с *нейронными сетями*.
- **SII** - формы работы с базой данных системы.
- **LearningAlgorithms** - библиотека *алгоритмов обучения*.  
- **DataBase** - папка, содержащая текущую версию SQLite БД проекта: **SII.db**. При сборке проекта необходимо положить данный файл в папку, где будет происходить сборка.

####reports
Отчет и презентация к выпускной работе должны храниться в папке вида **smirnov-michael**. Отчет должен иметь название **bachelor-graduation-report** (или **magister-graduation-report**). Презентация должна иметь имя такого же плана, только **report** заменяется на  **presentation**.
####tech-doc
Актуальная техническая документация под каждую часть проекта хранится в соответствующей папке:

- common - документы, имеющие отношение к ИСИАД в целом.
- neural-networks
- decision-trees
- learning-algorithms
- data-base-access
- data-processing
- gui
####working-doc
Текущая документация, определяющая и координирующая ведущиеся работы, хранится в следующих папках:

- common
- neural-networks
- decision-trees
- learning-algorithms
- data-base-access
- data-processing
- gui