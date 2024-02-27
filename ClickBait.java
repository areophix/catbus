import static java.lang.System.*;
import java.util.Scanner;

public class ClickBait {
	public static void main(String args[]) 
	{
		Scanner input = new Scanner(in);
		
		double circleX, circleY, circleWidth;
		int upperX, upperY, rectangleWidth, rectangleLength;
		double x,y;
		boolean isCircle, isRectangle;
		// 15 20 40 95 205 40 350 95 210
		out.println("Enter in x-coordinate of circle:");
		circleX = input.nextDouble();
		out.println("Enter in y-coordinate of circle:");
		circleY = input.nextInt();
		out.println("Enter in width of circle:");
		circleWidth = input.nextInt();
		out.println("Enter in x-coordinate of rectangle:");
		upperX = input.nextInt();
		out.println("Enter in y-coordinate of rectangle:");
		upperY = input.nextInt();
		out.println("Enter in width of rectangle:");
		rectangleWidth = input.nextInt();
		out.println("Enter in height of rectangle:");
		rectangleLength = input.nextInt();
		out.println("Enter x-coordinate of mouse click:");
		x = input.nextDouble();
		out.println("Enter y-coordinate of mouse click:");
		y = input.nextDouble();


		isCircle = checkCircle(circleX, circleY, circleWidth, x, y);
		isRectangle = checkRect(upperX, upperY, rectangleWidth, rectangleLength, x, y);
		printResult(isCircle, isRectangle);
        //System.out.println(upperX + " " + upperY + " " + rectangleWidth + " " + rectangleLength + " " + x + " " + y);
        //System.out.println(" | " + circleX + " " + circleY + " " + circleWidth);	
		input.close();
	}
	
	public static boolean checkCircle(double x, double y, double r, double x_click, double y_click) {
	    
	    double center_x = x+r/2;
	    double center_y = y+r/2;
	    
	    double dist = Math.sqrt(Math.pow((center_x-x_click), 2) + Math.pow((center_y-y_click), 2));
	    // use pythagorian(?) theorem to calculate distance between click and center of circle

	    return dist <= r/2; // if click distance from center is less than radius, click must be inside circle
	    
	}
	
	public static boolean checkRect(double x, double y, double w, double l, 
	double x_click, double y_click) {

        boolean within_x = x_click >= x && x_click <= x+w;
	    boolean within_y = y_click >= y && y_click <= y+l;
	    
	    return within_x && within_y;
	    
	}
	
	public static void printResult(boolean c, boolean r) {
	    if (c) {
	        System.out.println("circle");
	    }
	    else if (r) {
	        System.out.println("rectangle");
	    }
	    else {
	        System.out.println("neither");
	    }
	}
}
