% BaseFigure.m
% Reads Base.csv with #! header lines and plots the numeric data

clear; clc;

filename = 'Link1.csv';

% Detect import options
opts = detectImportOptions(filename);

% The header lines starting with "#!" are not real data,
% so we tell MATLAB to treat them as comments.
opts.CommentStyle = '#!';

% Now read the data
data = readmatrix(filename, opts);

% Remove any missing rows caused by blank lines
data = data(~isnan(data));

% Plot the data
figure;
plot(data, 'LineWidth', 2);
grid on;

title('Link1.csv Data Plot');
xlabel('Index');
ylabel('Pulses');

% Basic stats
fprintf('Loaded %d data points.\n', length(data));
fprintf('Min value: %g\n', min(data));
fprintf('Max value: %g\n', max(data));

fprintf('Mean value: %g\n', mean(data));
