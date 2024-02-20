interface Measures {
	code: number;
	'code/total': number;
	data: number;
	'data/total': number;
}

interface Commit {
	timestamp: number;
	git_hash: string;
	measures: Measures;
	description: string;
}

export default interface Dataset {
	[project: string]: {
		[version: string]: {
			dol: Commit[];
		};
	};
}
