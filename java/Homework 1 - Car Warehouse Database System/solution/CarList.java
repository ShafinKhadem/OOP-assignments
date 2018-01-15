import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.StringTokenizer;

class Car {
	private String carReg, colour1, colour2, colour3, carMake, carModel;
	//only colours can contain empty space inside, all strings are caseInsensitive
	private int yearMade, price;
	
	public Car (String carReg, int yearMade, String colour1, String colour2, String colour3, String carMake, String carModel, int price) {
		this.carReg = carReg;
		this.colour1 = colour1;
		this.colour2 = colour2;
		this.colour3 = colour3;
		this.carMake = carMake;
		this.carModel = carModel;
		this.yearMade = yearMade;
		this.price = price;
	}
	
	public Car () {
	}
	
	public String getCarReg () {
		return carReg;
	}
	
	public String getCarMake () {
		return carMake;
	}
	
	public String getCarModel () {
		return carModel;
	}
	
	public String getColour1 () {
		return colour1;
	}
	
	public String getColour2 () {
		return colour2;
	}
	
	public String getColour3 () {
		return colour3;
	}
	
	public int getYearMade () {
		return yearMade;
	}
	
	public int getPrice () {
		return price;
	}
}

public class CarList {
	
	private static final String FILE_NAME = "cars.txt";
	private static Scanner in = new Scanner (System.in);
	
	private static ArrayList<Car> carList = new ArrayList<> ();
	
	private static int search (String reg) {
		int sz = carList.size ();
		for (int i = 0; i<sz; i++) {
			if (carList.get (i).getCarReg ().equalsIgnoreCase (reg)) {
				return i;
			}
		}
		return -1;
	}
	
	private static void search (String make, String model) {
		int sz = carList.size ();
		boolean flg = false;
		for (int i = 0; i<sz; i++) {
			Car car = carList.get (i);
			if (car.getCarMake ().equalsIgnoreCase (make) && (model.equals ("ANY")||car.getCarModel ().equalsIgnoreCase (model))) {
				displayAllInfo (i);
				flg = true;
			}
		}
		if (!flg) {
			System.out.println ("No such car found");
		}
	}
	
	private static void add (Car car) {
		carList.add (car);
	}
	
	private static void delete (String reg) {
		//first search the car using registration, then delete using index
		int idx = search (reg);
		if (idx == -1) {
			System.out.println ("There is no car with this registration number");
		}
		else {
			carList.remove (idx);
		}
	}
	
	private static void displayAllInfo (int idx) {
		Car car = carList.get (idx);
		System.out.println ("Car's all info");
		System.out.println ("registration no: "+car.getCarReg ());
		System.out.println ("year made: "+car.getYearMade ());
		System.out.println ("colour1: "+car.getColour1 ());
		System.out.println ("colour2: "+car.getColour2 ());
		System.out.println ("colour3: "+car.getColour3 ());
		System.out.println ("maker: "+car.getCarMake ());
		System.out.println ("model: "+car.getCarModel ());
		System.out.println ("price: $"+car.getPrice ());
	}
	
	private static Car inputCar () {
		//			String carReg, int yearMade, String colour1, String colour2, String colour3, String carMake, String carModel, int price
		System.out.println ("Enter registration no");
		String reg = in.next ();
		System.out.println ("Enter year made");
		int year = in.nextInt ();
		System.out.println ("Enter colour1");
		String c1 = in.next ();
		System.out.println ("Enter colour2");
		String c2 = in.next ();
		System.out.println ("Enter colour3");
		String c3 = in.next ();
		System.out.println ("Enter maker");
		String make = in.next ();
		System.out.println ("Enter model");
		String model = in.next ();
		System.out.println ("Enter price");
		int price = in.nextInt ();
		return new Car (reg, year, c1, c2, c3, make, model, price);
	}
	
	private static void readFile () {
		try {
			BufferedReader br = new BufferedReader(new FileReader (FILE_NAME));
			String line = br.readLine ();
			String[] ss;
			while (line != null) {
				ss = line.split (",");
				Car tempCar = new Car (ss[0], Integer.parseInt (ss[1]), ss[2], ss[3], ss[4], ss[5], ss[6], Integer.parseInt (ss[7]));
				carList.add (tempCar);
				line = br.readLine();
			}
			br.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private static void saveFile () {
		try {
			BufferedWriter bw = new BufferedWriter(new FileWriter (FILE_NAME));
			int sz = carList.size ();
			for (Car car : carList) {
				bw.write (
						car.getCarReg ()+","+Integer.toString (car.getYearMade ())+","+car.getColour1 ()+","+car.getColour2 ()+","+car.getColour3 ()+","+car.getCarMake ()+","+car.getCarModel ()+","+Integer.toString (car.getPrice ()));
				bw.write ("\n");
			}
			bw.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		readFile ();
		boolean exit = false;
		while (!exit) {
			System.out.println ("(1) Search Cars\n"+"(2) Add Car\n"+"(3) Delete Car\n"+"(4) Exit System");
			int opt = in.nextInt ();
			if (opt == 1) {
				boolean back = false;
				while (!back) {
					System.out.println ("Car Searching Options:\n"+"(1) By Registration Number\n"+"(2) By Car Make and Car Model\n"+"(3) Back to Main Menu");
					int sopt = in.nextInt ();
					if (sopt == 1) {
						System.out.println ("Please input the registration number");
						String toSearch = in.next ();
						int idx = search (toSearch);
						if (idx == -1) {
							System.out.println ("No such car with this Registration Number");
						}
						else {
							displayAllInfo (idx);
						}
					}
					else if (sopt == 2) {
						System.out.println ("Please input the car maker");
						String make = in.next ();
						System.out.println ("Please input the car model");
						String model = in.next ();
						search (make, model);
					}
					else if (sopt == 3) {
						back = true;
					}
					else {
						System.out.println ("Not a valid option. Please input between 1 to 3");
					}
				}
			}
			else if (opt == 2) {
				add (inputCar ());
			}
			else if (opt == 3) {
				System.out.println ("Please input the registration number");
				String reg = in.next ();
				delete (reg);
			}
			else if (opt == 4) {
				exit = true;
			}
			else {
				System.out.println ("Not a valid option. Please input between 1 to 4");
			}
		} 
		saveFile ();
	}
}
