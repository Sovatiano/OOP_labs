using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace OOP_lab5_Savostianov
{
    public class Department_Savostianov
    {
        [JsonPropertyName("employees")]
        private List<Employee_Savostianov> employees;

        public Department_Savostianov()
        {
            employees = new List<Employee_Savostianov>();
        }

        public void AddEmployee()
        {
            Employee_Savostianov employee = new Employee_Savostianov();
            employee.ReadFromConsole();
            employees.Add(employee);
        }

        public void AddManager()
        {
            Manager_Savostianov manager = new Manager_Savostianov();
            manager.ReadFromConsole();
            employees.Add(manager);
        }

        public void ClearList()
        {
                employees.Clear();
                Console.WriteLine("\nСписок очищен");
        }

        public void DisplayAllEmployees()
        {
            foreach (var employee in employees)
            {
                employee.DisplayInfo();
                Console.WriteLine();
            }
        }
        public void WriteToFile()
        {
            if (!employees.Any())
            {
                Console.WriteLine("\nСписок пуст.");
                return;
            }
            else
            {
                Console.Write("\nВведите название файла (без расширения) для сохранения: ");
                var filename = Console.ReadLine();

                JsonSerializerOptions options = new JsonSerializerOptions
                {
                    WriteIndented = true
                };

                string jsonString = JsonSerializer.Serialize(employees, options);
                File.WriteAllText(filename + ".json", jsonString);

                Console.WriteLine("\nДанные успешно сохранены.");
            }
        }

        public void ReadFromFile()
        {
            Console.Write("\nВведите название файла для загрузки: ");
            var filename = Console.ReadLine();

            if (File.Exists(filename + ".json"))
            {
                try
                {
                    string jsonString = File.ReadAllText(filename + ".json");
                    employees = JsonSerializer.Deserialize<List<Employee_Savostianov>>(jsonString);

                   if (employees.Any()) {
                        Console.WriteLine("\nДанные успешно загружены.");
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Ошибка при загрузке данных: {ex.Message}");
                }
            }
            else
            {
                Console.WriteLine("Файл не найден.");
            }
        }
    }
}
