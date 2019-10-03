import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.lang.Math;
import java.text.DecimalFormat;
import java.util.concurrent.TimeUnit;

/*<applet code="color" width=1000 height=800></applet>*/

public class color  extends Applet implements ActionListener
{
   DecimalFormat df = new DecimalFormat("######.##");
	TextField xinput,yinput,output1,output2,output3;
   Button compute;
	final double bicep = 81, forearm=81;
	final double bicepsq = Math.pow(81,2), forearmsq = Math.pow(81,2);
   double fact=0;
	double x=0,y=0;
	double oldx=0,oldy=0;
	double q1=0,q2=0;
	double a1, a2;
	double b=0, bsq=0;
	double olda1=0,oldq1=0;
   public void init()
   {
		setBackground(Color.white);
		Panel firstRow = new Panel();
		Panel secondRow = new Panel();
		Panel thirdRow = new Panel();
		Panel fourthRow = new Panel();

		compute=new Button("Compute");
      Label xinp=new Label("Enter x component :");
		Label yinp=new Label("Enter y component:");
      Label opt1=new Label("The distance reached is: ");
		Label opt2=new Label("The first angle is: ");
		Label opt3=new Label("The second angle is: ");
      xinput=new TextField(10);
		yinput = new TextField(10);
      output1=new TextField(10);
		output2=new TextField(10);
		output3=new TextField(10);

      firstRow.add(xinp);
      firstRow.add(xinput);
		firstRow.add(yinp);
		firstRow.add(yinput);
		secondRow.add(compute);
      thirdRow.add(opt1);
      thirdRow.add(output1);
      fourthRow.add(opt2);
      fourthRow.add(output2);     
		fourthRow.add(opt3);
      fourthRow.add(output3);

      output1.setEditable(false);
      output2.setEditable(false);
      output3.setEditable(false);
		xinput.setText("0");
		yinput.setText("0");
      xinput.addActionListener(this);
		yinput.addActionListener(this);
      output1.addActionListener(this);
      output2.addActionListener(this);
      output3.addActionListener(this);
      compute.addActionListener(this);
		add(firstRow);
		add(secondRow);
		add(thirdRow);
		add(fourthRow);
	}
   public void actionPerformed(ActionEvent ae)
   {  
		olda1=a1;
		oldq1 = q1;
   	String str=ae.getActionCommand();
     	if(str.equals("Compute"))
      {
			oldx=x;
			oldy=y;
			x=Double.parseDouble(xinput.getText());
			y=Double.parseDouble(yinput.getText());
			bsq = Math.pow(x,2.0) + Math.pow(y,2.0);
			b = Math.hypot(x,y);
			q1 = Math.atan2(y,x);
			q2 = Math.acos((bsq+bicepsq-forearmsq)/(2*forearm*b));
			a1 = (q1+q2);  //in radians
			a2 =( Math.acos((bicepsq+forearmsq-bsq)/(2*forearm*bicep)));
         if(bsq<=26406)
         {  
				fact=1;
         	output1.setText(""+df.format(b));
				output2.setText(""+df.format(Math.toDegrees(a1)));
				output3.setText(""+df.format(Math.toDegrees(a2)));
         }
         else
        		fact=-1;                         
      }
		repaint();
	}
   public void paint(Graphics g)
   {         
   	if(fact==-1) 
		{
      	output1.setText("0");
         g.drawString("Sorry, this point is unreachable with this arm",10,200); 
		}
		else if(fact >0);
		{
			g.fillRect(230,680,160,13);
			g.fillOval(275,670,20,20);
			double red=0, green=0,blue=0;
			double frequency=.00007;
			double nx,ny;
			double i=0;
			double step = .002;
			double tempb = b;
			for(double j=0;j<b;j+=step)
			{
				nx = oldx + (x-oldx)*j/b;
				ny = oldy + (y-oldy)*j/b;
				bsq = Math.pow(nx,2.0) + Math.pow(ny,2.0);
				b = Math.hypot(nx,ny);
				q1 = Math.atan2(ny,nx);
				q2 = Math.acos((bsq+bicepsq-forearmsq)/(2*forearm*b));
				a1 = (q1+q2);  //in radians	
				a2 =( Math.acos((bicepsq+forearmsq-bsq)/(2*forearm*bicep)));  //System.out.println("before draw");
				red   = Math.sin(frequency*i + 0) * 127 + 128;
				green = Math.sin(frequency*i + 2) * 127 + 128;
				blue  = Math.sin(frequency*i + 4) * 127 + 128;	
				i+=1;	
				g.setColor(new Color((int)red,(int)green,(int)blue));
				g.drawLine(285,680,285+((int)((3*bicep*Math.cos(a1)))),680-((int)(3*bicep*Math.sin(a1))));
				g.drawLine(285+((int)(3*bicep*Math.cos(a1))),680-((int)(3*bicep*Math.sin(a1))),285+((int)(3*b*(Math.cos(q1)))),680-((int)((3*b*Math.sin(q1))))); 
				g.setColor(Color.black);
				g.fillOval(275,670,20,20);
 				g.fillOval(275+(int)((3*bicep*Math.cos(a1))),670-(int)(3*bicep*Math.sin(a1)),20,20);
				g.fillRect(230,680,160,13); //System.out.println("after draw");
					/*try 
					{
    					Thread.sleep(1);
					}catch(InterruptedException ex) 
					{
    					Thread.currentThread().interrupt();
					}*/
				System.out.println("in for, j: "+j);
			}			
	   }
	}
}
