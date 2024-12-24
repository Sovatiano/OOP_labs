using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace OOP_lab5_Savostianov
{
    [Serializable]
    [XmlType(TypeName = "Manager")]
    public class Manager_Savostianov : Employee_Savostianov
    {
        private string department;
        private int employees_num;

        public Manager_Savostianov(int employeeID, string name, string surname, double salary, string department, int employees_num)
            : base(employeeID, name, surname, salary)
        {
            this.department = department;
            this.employees_num = employees_num;
        }

        public Manager_Savostianov()
        {
        }

        public string Department
        {
            get { return department; }
            set { department = value; }
        }

        public int EmployeesNum
        {
            get { return employees_num; }
            set { employees_num = value; }
        }

        public override void DisplayInfo()
        {
            base.DisplayInfo();
            Console.WriteLine($"Отдел: {department}, Количество сотрудников: {employees_num}");
        }

        public override void ReadFromConsole()
        {
            base.ReadFromConsole();

            Console.Write("Введите отдел менеджера: ");
            department = Console.ReadLine();

            Console.Write("Введите количество сотрудников, которыми управляет менеджер: ");
            while (!int.TryParse(Console.ReadLine(), out employees_num) || employees_num < 0)
            {
                Console.WriteLine("Ошибка! Введите корректное положительное числовое значение.");
                Console.Write("Введите количество сотрудников, которыми управляет менеджер: ");
            }
        }
    }
}
