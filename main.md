```cpp
void test(Person const& person)
{
    std::cout << "test: " << person.name() << '\n';
    
    if (person.grade() == 10 || person.salary() > 1'000'000)
    {
        save(Status::success, person.id());
    }
    else
    {
        save(Status::failure, person.id());
    }
}
```
### Элементы нормального ветвления:
1) if (person.grade() == 10 || person.salary() > 1'000'000)

   if создает два пути выполнения: true-ветвь и false-ветвь
2) оператор ||

    Выполняется short-circuit evaluation. 
    Если person.grade() == 10 истинно, person.salary() не вычисляется
### Элементы, которые могут генерировать исключения:
person.name()

person.grade()

person.salary()

person.id() 

std::cout << "test: " << person.name() << '\n';, например, при неудачной записи

save(Status::success, person.id());

save(Status::failure, person.id());

person.grade() == 10

person.salary() > 1'000'000 