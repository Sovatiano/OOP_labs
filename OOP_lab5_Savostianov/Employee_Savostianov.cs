using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace OOP_lab5_Savostianov
{
    [JsonDerivedType(typeof(Employee_Savostianov), typeDiscriminator: "employee")]
    [JsonDerivedType(typeof(Manager_Savostianov), typeDiscriminator: "manager")]
    public class Employee_Savostianov
    {
        private int employeeID;
        private string name;
        private string surname;
        private double salary;

        public Employee_Savostianov(int employeeID, string name, string surname, double salary)
        {
            this.employeeID = employeeID;
            this.name = name;
            this.surname = surname;
            this.salary = salary;
        }

        public Employee_Savostianov()
        {
        }

        public int EmployeeID
        {
            get { return employeeID; }
            set { employeeID = value; }
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string Surname
        {
            get { return surname; }
            set { surname = value; }
        }

        public double Salary
        {
            get { return salary; }
            set { salary = value; }
        }

        public virtual void DisplayInfo()
        {
            Console.WriteLine($"ID: {employeeID}, Имя: {name}, Фамилия: {surname}, Зарплата: {salary}");
        }

        public virtual void ReadFromConsole()
        {
            Console.WriteLine("Введите данные сотрудника:");

            Console.Write("Введите ID сотрудника: ");
            while (!int.TryParse(Console.ReadLine(), out employeeID))
            {
                Console.WriteLine("Ошибка! Введите корректное числовое значение для ID.");
                Console.Write("Введите ID сотрудника: ");
            }

            Console.Write("Введите имя сотрудника: ");
            name = Console.ReadLine();

            Console.Write("Введите фамилию сотрудника: ");
            surname = Console.ReadLine();

            Console.Write("Введите зарплату сотрудника: ");
            while (!double.TryParse(Console.ReadLine(), out salary) || salary < 0)
            {
                Console.WriteLine("Ошибка! Введите корректное положительное числовое значение для зарплаты.");
                Console.Write("Введите зарплату сотрудника: ");
            }
        }

    }
}
