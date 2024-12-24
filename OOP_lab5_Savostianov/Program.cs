using OOP_lab5_Savostianov;

internal class Program
{
    static void ShowMenu()
    {
        Console.WriteLine("\n1) Добавить сотрудника");
        Console.WriteLine("2) Добавить менеджера");
        Console.WriteLine("3) Показать список сотрудников");
        Console.WriteLine("4) Считать список из файла");
        Console.WriteLine("5) Сохранить список в файл");
        Console.WriteLine("6) Очистить список");
        Console.WriteLine("0) Выход");
        Console.WriteLine("===============================");
        Console.Write("\nВыберите пункт меню: ");
    }

    public static T check_input<T>(T min, T max) where T : IComparable<T>
    {
        T input;
        while (true)
        {
            try
            {

                input = (T)Convert.ChangeType(Console.ReadLine(), typeof(T));


                if (input.CompareTo(min) >= 0 && input.CompareTo(max) <= 0)
                {
                    return input;
                }
                else
                {
                    Console.Write($"\nВведите корректное значение (от {min} до {max}): ");
                }
            }
            catch
            {
                Console.Write($"\nВведите число от ({min} до {max}): ");
            }
        }
    }

    static void Main(string[] args)
    {
        Department_Savostianov employees = new Department_Savostianov();
        for (; ; )
        {
            ShowMenu();
            int menuItem = check_input(0, 6);

            switch (menuItem)
            {
                case 1:
                    employees.AddEmployee();
                    break;
                case 2:
                    employees.AddManager();
                    break;
                case 3:
                    employees.DisplayAllEmployees();
                    break;
                case 4:
                    employees.ReadFromFile();
                    break;
                case 5:
                    employees.WriteToFile();
                    break;
                case 6:
                    employees.ClearList();
                    break;
                case 0: return;
            }

        }
    }
}