function main


% COBWEB
netz = 4;
int_method = 1;
energy_plot = 1;

%Spinnennetz
if netz == 1
%%{
  nc = 5;
  c = 3;

  fixpoints = [nc*c+2 - nc: nc*c+1];
  d = 0.2;
  k = 1;  %Federkonstante
  m = 1;  %Masse
  g = 0.01;  #Gravitation
  friction = 1;  %Reibungskoeffizient
  verb1 = connections(nc,c);
  p_0 = [0,0,0.5,-0.5];
  C1 = matrix(nc,c,p_0);
  C2 = realistic_cobweb(d,verb1,C1){1};
  C3(1:2,:) = C2;
  P = [transpose(p_0(3:4)),zeros(2,length(C2)-1)];
  C3(3:4,:) = P;
  verb2 = realistic_cobweb(d,verb1,C1){2};  
  verb = imp_verb(verb2);
  DistMat = dist_neu(length(C3),C3,verb);
  length(DistMat);
  n = length(C3);
  s = 1;
  C = stretch(C3,s);
%}
endif

% HÄNGENDE KETTE
if netz == 2
  %%{
  n = 30;
  fixpoints = [1,n];
  k = 1;  %Federkonstante
  m = 3;  %Masse
  g = 1;  #Gravitation
  friction = 0;  %Reibungskoeffizient
  verb = {{2}};
  for i = 2:(n-1)
    verb{i}{1} = i-1;
    verb{i}{2} = i+1;
  end
  verb{n}{1} = n-1;
  C = [(1/n)* 1:n; 1:n; zeros(1,n); zeros(1,n)];
  DistMat = dist_neu(n,C,verb);
  %}
endif
% LIANE
if netz == 3
%%{
  n = 20;
  fixpoints = [1];
  k = 10;  %Federkonstante
  m = 1;  %Masse
  g = 10;  #Gravitation
  friction = 0;  %Reibungskoeffizient
  verb = {{2}};
  for i = 2:(n-1)
    verb{i}{1} = i-1;
    verb{i}{2} = i+1;
  end
  verb{n}{1} = n-1;
  C = [(1/n)* 1:n; 1:n; zeros(1,n); zeros(1,n)];
  DistMat = dist_neu(n,C,verb);
%}
endif
% Gitter
if netz == 4
%%{
  h = 5;
  w = 4;
  d = 0.1
  n = h*w;
  fixpoints = [(n-w+1):n];
  k = 2;  %Federkonstante
  m = 1;  %Masse
  g = 0.05;  #Gravitation
  friction = 0;  %Reibungskoeffizient
  C1 = [repmat(1:w,1,h); floor(((1:n) - 1)/w); zeros(1,n); 0.2 zeros(1,n-1)];
  C1(3,n/2) = 2;
  C1(4,n/2) = -2;
  verb1 = gitter(w,h);
  C2 = realistic_cobweb(d,verb1,C1){1};
  C3(1:2,:) = C2;
  P = zeros(2,length(C2));
  C3(3:4,:) = P;
  verb2 = realistic_cobweb(d,verb1,C1){2};  
  verb = imp_verb(verb2);
  DistMat = dist_neu(length(C3),C3,verb);
  length(DistMat);
  n = length(C3);
  s = 1;
  C = stretch(C3,s);
%}
endif


  
  
  
  gamma = 0.5;
  beta = 0.25;
  
  tau = 1/8;
  T = 100;
  framerate = 4 % jedes ***-te Bild wird gezeichnet
  timesteps = floor(T/tau)

  
  X_initial = transpose(transpose(C)(:));
  X = X_initial; % Zeilenmatrix
  
  positions_stored = zeros(2*n,timesteps);


  figure(2)
  clf;
  for t = 1:timesteps
    t
    if int_method == 1
      
    %Verlet Method
    %%{
    f_temp = f(X,n,fixpoints,verb,tau,k,m,friction,g,DistMat);
    temp_velocity = X(2*n+1:4*n) + tau/2 * f_temp;
    X(1:2*n) = X(1:2*n) + tau * temp_velocity;
    X(2*n+1:4*n) = X(2*n+1:4*n) + tau/2 * f(X,n,fixpoints,verb,tau,k,m,friction,g,DistMat) +  tau/2 * f_temp;
    %}
    %initale Werte für Fixpunktiteration
    
    endif
    if int_method == 2
    %%{

    x_old = X(1,1:(2*n));
    v_old = X(1,(2*n+1):(4*n));
    a_old = 1/m * f(X,n,fixpoints,verb,tau,k,m,friction,g,DistMat);

    x_new = x_old;
    v_new = v_old;
    a_new = a_old;



    %Fixpunktiteration
    iter = 0;

    do
      v_new_temp = v_old + (1-gamma)*tau*a_old + gamma*tau*a_new;
      x_new_temp = x_old + tau* v_new + tau**2/2*((1-2*beta)*a_old + 2*beta*a_new);
      a_new_temp = 1/m * f([x_new,v_new],n,fixpoints,verb,tau,k,m,friction,g,DistMat); %X durch X_new ersetzten

      error = norm(x_new - x_new_temp);

      v_new = v_new_temp;
      x_new = x_new_temp;
      a_new = a_new_temp;


      iter += 1;
    until(iter > 50 || error < 10**(-3))


    %X aus x_new,v_new berechnen
    X = [x_new,v_new];
    endif

    %}


    positions_stored(:,t) = X(1:2*n);




    if energy_plot == 1
      %%{
      if t!=1
        energy_temp = energy;
        kin_energy_temp = kin_energy;
        spannungs_energy_temp  = spannungs_energy;
        potentielle_energy_temp = potentielle_energy;
      end
      energy = 0;
      kin_energy = 0;
      spannungs_energy = 0;
      potentielle_energy = 0;
      for i = 1:n
        kin_energy += 1/2 * m * 1/tau * norm([X(1,2*n+i),X(1,3*n+i)])^2; #kinetische Energie
        for l = 1 : length(verb{i}) 
          j = DistMat{i}{l}(1);% alle Verbindungen zu i
          d = DistMat{i}{l}(2);
          spannungs_energy += 1/4 * 1/tau * k * (norm([X(1,i)-X(1,j),X(1,n+i)-X(1,n+j)]) - d)^2; #spann/potentielle Ernergie. Der Fakotr 1/4 kommt davon, dass die Federn doppelt gezählt werden.
        end
        potentielle_energy += m*g*X(1,n+i);
      end
      energy = kin_energy + spannungs_energy + potentielle_energy;
      if t!=1
        %axis
        xlabel ("rot: totale Energie,  blau: kin,  grün: spann,  gelb: pot"); 
        plot([t/timesteps,(t+1)/timesteps],[energy_temp,energy],'r-'); hold on;
        plot([t/timesteps,(t+1)/timesteps],[kin_energy_temp,kin_energy],'bo'); hold on;
        plot([t/timesteps,(t+1)/timesteps],[spannungs_energy_temp,spannungs_energy],'g--'); hold on;
        plot([t/timesteps,(t+1)/timesteps],[potentielle_energy_temp,potentielle_energy],'yx'); hold on;
        energy; #output im Befehlsfenster
      end
      %}
    endif
  end


  figHandle = figure(1);
  figure(1);

  %axis([-1,9,-25,10]);
  %axis([-3,3*w+1,-h,3*h+1]);
  axis([-1,5,-8,5]);
  clf;

  
  for t = 1:timesteps
    t
    if rem(t,framerate) == 0
      clf;
      x = positions_stored(1:n,t); % die x Werte der n Punkte
      y = positions_stored(n+1:2*n,t);  % die y Werte der n Punkte

        % Zeichnet die Punkte.
      %axis([-10,10,-10,10]);
      %axis([-3,2*w+1,-h,2*h+1]);
      axis([-1,5,-8,5]);

      for i = 1:n
        for j = cell2mat(verb{i})
          line([x(i),x(j)],[y(i),y(j)]);
        end
      end
      drawnow;
      MakeGif(figHandle, 'test.gif');
    end
  end
end

main() %führe alles aus
