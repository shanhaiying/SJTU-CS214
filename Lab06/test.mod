/*********************************************
 * OPL 12.9.0.0 Model
 * Author: david
 * Creation Date: Apr 12, 2020 at 4:12:56 AM
 *********************************************/
{int} Products=...;//Rank of Products
{string} Tools=...;//Name of tools
int ToolMaxNumber[Tools]=...;//The number of each tool
{int} firstmonth=...;//6 months
{int} midmonths=...;
{int} lastmonth=...;
{int} months=...;
float Price[Products]=...;//the price of each kind of product
float use[Tools][Products]=...;//the duration of use of a tool to produce per product
int MaxNeed[Products][months]=...;//the maxmimal need for a product every month
float StorationCost=...;//cost to storage a product
int WorkHourPerMonth=...;
int StoreCapacity=...;
int DesiredStoration=...;

dvar int+ ToolRepairNumber[Tools][months];//How many instances of tools are repaired each month
dvar int+ Produce[Products][months];
dvar int+ Sell[Products][months];
dvar int+ Hold[Products][months];
dvar int+ StoreCost;
dvar int+ SellPrice;

maximize
  sum(i in Products)
    sum(j in months)
      (Price[i]*Sell[i][j]-StorationCost*Hold[i][j]);
subject to{
    sum(i in Products)
      sum(j in months)
        Price[i]*Sell[i][j]==SellPrice;
    sum(i in Products)
      sum(j in months)
        StorationCost*Hold[i][j]==StoreCost;

    forall(i in Products)
      (Produce[i][1]==Hold[i][1]+Sell[i][1]);
      
    forall(i in Products)
      forall(j in midmonths)
        (Produce[i][j]+Hold[i][j-1]==Sell[i][j]+Hold[i][j]);
    
    forall(i in Products)
      forall(j in months)
        (Sell[i][j]<=MaxNeed[i][j]);
    
    forall(i in Products)
      forall(j in months)
        (Hold[i][j]<=StoreCapacity);
    
    forall(i in Tools)
      forall(j in months)
        ToolRepairNumber[i][j]<=ToolMaxNumber[i];
        
    forall(i in Tools)
      sum(j in months)
        ToolRepairNumber[i][j]==ToolMaxNumber[i];
    
    forall(j in months)
        forall(k in Tools)
          sum(i in Products)
            use[k][i]*Produce[i][j]<=(ToolMaxNumber[k]-ToolRepairNumber[k][j])*WorkHourPerMonth;
            
    forall(i in Products)
      forall(j in lastmonth)
      Hold[i][j]==DesiredStoration;    

}